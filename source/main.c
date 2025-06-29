#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

void setup_wii() {
    VIDEO_Init();
    WPAD_Init();
    
    rmode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

void show_thomas_message() {
    printf("THOMAS THE TRAIN SOUND!\n");
    printf("*BASS BOOSTED NOISES*\n");
    printf("CHOO CHOO CHOO!\n");
    printf("🚂💨💨💨\n\n");
}

int main() {
    setup_wii();
    
    printf("\x1b[2;0H");
    printf("╔══════════════════════════════════╗\n");
    printf("║        HE HE HE HA APP!          ║\n");
    printf("║             v1.0                 ║\n");
    printf("╚══════════════════════════════════╝\n\n");
    
    printf("🎮 Controls:\n");
    printf("• Press [1] for Thomas Train sound\n");
    printf("• Press [HOME] to exit\n\n");
    
    printf("HE HE HE HA! 😂\n");
    printf("Ready to play some sounds!\n\n");
    
    int sound_count = 0;
    
    while(1) {
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);
        
        if (pressed & WPAD_BUTTON_HOME) {
            printf("\n👋 Thanks for playing!\n");
            printf("HE HE HE HA - Goodbye!\n");
            break;
        }
        
        if (pressed & WPAD_BUTTON_1) {
            sound_count++;
            printf("[Sound #%d] ", sound_count);
            show_thomas_message();
        }
        
        VIDEO_WaitVSync();
    }
    
    return 0;
}