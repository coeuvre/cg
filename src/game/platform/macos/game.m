#if !__has_feature(objc_arc)
    #error "ARC is off"
#endif

#import <Cocoa/Cocoa.h>
#include <crt_externs.h> /* for _NSGetProgname */

#include <cg/core.h>
#include <cg/game.h>

@interface CGOpenGLView : NSOpenGLView {
    @public struct cg_game_config *config;

    CVDisplayLinkRef display_link;
}
- (CVReturn)getFrameForTime: (const CVTimeStamp *)output;
@end

static CVReturn display_link_callback(CVDisplayLinkRef display_link,
                                      const CVTimeStamp *now,
                                      const CVTimeStamp *output,
                                      CVOptionFlags flags,
                                      CVOptionFlags *flags_out, void *context)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [(__bridge CGOpenGLView *)context getFrameForTime:output];
    });
    return kCVReturnSuccess;
}

@implementation CGOpenGLView
- (void)prepareOpenGL
{
    /* Enable VSync */
    GLint swap_interval = 1;
    [[self openGLContext] setValues:&swap_interval
                       forParameter:NSOpenGLCPSwapInterval];

    CVDisplayLinkCreateWithActiveCGDisplays(&display_link);
    CVDisplayLinkSetOutputCallback(display_link, &display_link_callback,
                                   (__bridge void * _Nullable)(self));

    CGLContextObj context = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj pixelformat = [[[self openGLContext] pixelFormat]
                                     CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(display_link,
                                                      context, pixelformat);

    CVDisplayLinkStart(display_link);
}

- (CVReturn)getFrameForTime: (const CVTimeStamp *)output
{
    float dt = 0.016667f;

    uint64_t start = cg_current_counter();

    if (config->lifecycle->update) {
        config->lifecycle->update(config->userdata, dt);
    }

    if (config->lifecycle->render) {
        config->lifecycle->render(config->userdata);
    }

    uint64_t end = cg_current_counter();
    uint64_t frame_cost = cg_counter2ns(end - start);
    frame_cost = cg_ns2ms(frame_cost);
    CG_DEBUG("Frame cost: %"PRIu64"ms", frame_cost);

    return kCVReturnSuccess;
}

- (void)dealloc
{
    CVDisplayLinkRelease(display_link);
}
@end

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    @public struct cg_game_config *config;
}

@end

@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    if (config->lifecycle->init) {
        config->lifecycle->init(config->userdata);
    }
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    if (config->lifecycle->term) {
        config->lifecycle->term(config->userdata);
    }
}
@end

static void create_menu(NSApplication *app)
{
    NSMenu* bar = [[NSMenu alloc] init];
    [app setMainMenu:bar];

    NSMenuItem* item = [bar addItemWithTitle:@""
                                      action:NULL
                               keyEquivalent:@""];

    NSMenu* menu = [[NSMenu alloc] init];
    [item setSubmenu:menu];

    [menu addItemWithTitle:@"Quit"
                    action:@selector(terminate:)
             keyEquivalent:@"q"];

    // Prior to Snow Leopard, we need to use this oddly-named semi-private API
    // to get the application menu working properly.
    [app performSelector:@selector(setAppleMenu:) withObject:menu];
}

void cg_run_game(struct cg_game_config *config)
{
    if (config == 0) {
        return;
    }

    NSApplication *app = [NSApplication sharedApplication];
    AppDelegate *delegate = [[AppDelegate alloc] init];
    delegate->config = config;
    [app setDelegate:delegate];

    create_menu(app);

    [app setActivationPolicy:NSApplicationActivationPolicyRegular];
    CGOpenGLView *view = [[CGOpenGLView alloc] init];
    view->config = config;
    [view setWantsBestResolutionOpenGLSurface:YES];

    NSRect rect = NSMakeRect(0, 0, 800, 600);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                       NSWindowStyleMaskMiniaturizable;
    NSWindow *window = [[NSWindow alloc]
        initWithContentRect:rect
                  styleMask:style
                    backing:NSBackingStoreBuffered
                      defer:true];

    [window setContentView:view];
    [window makeFirstResponder:view];
    [window setTitle:@"CG Window"];
    [window center];
    [window setAcceptsMouseMovedEvents:YES];
    [window setRestorable:NO];
    [window makeKeyAndOrderFront:nil];

    [app activateIgnoringOtherApps:YES];
    [app run];
}
