#import <Cocoa/Cocoa.h>
// for _NSGetProgname
#include <crt_externs.h>
#include <OpenGL/gl.h>

#include <cg/core.h>
#include <cg/game/lifecycle.h>

@interface CGOpenGLView : NSOpenGLView
@end

@implementation CGOpenGLView
-(void) drawRect: (NSRect) bounds
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
    glFlush();
}
@end

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    struct cg_game_state *state;
}

@end

@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSOpenGLView *view = [[CGOpenGLView alloc] init];
    [view setWantsBestResolutionOpenGLSurface:YES];

    self->state = cg_game_startup();

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
    [window setAcceptsMouseMovedEvents:YES];
    [window setRestorable:NO];

    [window makeKeyAndOrderFront:nil];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    cg_game_shutdown(self->state);
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
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];

        create_menu(app);

        [app setActivationPolicy:NSApplicationActivationPolicyRegular];
        [app activateIgnoringOtherApps:YES];
        [app run];
    }

    return 0;
}
