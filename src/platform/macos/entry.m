#if !__has_feature(objc_arc)
    #error "ARC is off"
#endif

#import <Cocoa/Cocoa.h>
#include <crt_externs.h> /* for _NSGetProgname */

#include <cg/core.h>
#include <cg/game/lifecycle.h>

@interface CGOpenGLView : NSOpenGLView {
    @public struct cg_game_state *state;

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

    cg_game_update(state, dt);

    cg_game_render(state);

    return kCVReturnSuccess;
}

- (void)dealloc
{
    CVDisplayLinkRelease(display_link);
}
@end

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    @public struct cg_game_state *state;
}

@end

@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    cg_game_started(state);
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    cg_game_shutdown(state);
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

int main(int argc, const char * argv[])
{
    struct cg_game_state *state = cg_game_startup();

    NSApplication *app = [NSApplication sharedApplication];
    AppDelegate *delegate = [[AppDelegate alloc] init];
    delegate->state = state;
    [app setDelegate:delegate];

    create_menu(app);

    [app setActivationPolicy:NSApplicationActivationPolicyRegular];
    CGOpenGLView *view = [[CGOpenGLView alloc] init];
    view->state = state;
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

    return 0;
}
