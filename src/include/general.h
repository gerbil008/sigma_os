#ifndef GENERAL_H
#define GENERAL_H

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

static inline void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    __asm__ volatile (
        "cpuid"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(leaf)
    );
}

int has_invariant_tsc() {
    uint32_t eax, ebx, ecx, edx;

    // Extended Function 0x80000007
    cpuid(0x80000007, &eax, &ebx, &ecx, &edx);

    return (edx & (1 << 8)) != 0;  // Bit 8 = invariant TSC flag
}

#endif