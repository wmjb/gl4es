#include "gl4es.h"
#include "loader.h"
#include <dlfcn.h>

extern void *gles;

// Define function pointer types for NV_fence
typedef void (*glGenFencesNV_PTR) (GLsizei n, GLuint *fences);
typedef void (*glDeleteFencesNV_PTR) (GLsizei n, const GLuint *fences);
typedef void (*glSetFenceNV_PTR) (GLuint fence, GLenum condition);
typedef GLboolean (*glTestFenceNV_PTR) (GLuint fence);
typedef void (*glFinishFenceNV_PTR) (GLuint fence);
typedef void (*glGetFenceivNV_PTR) (GLuint fence, GLenum pname, GLint *params);
typedef GLboolean (*glIsFenceNV_PTR) (GLuint fence);

// Local function pointers
static glGenFencesNV_PTR gles_glGenFencesNV = NULL;
static glDeleteFencesNV_PTR gles_glDeleteFencesNV = NULL;
static glSetFenceNV_PTR gles_glSetFenceNV = NULL;
static glTestFenceNV_PTR gles_glTestFenceNV = NULL;
static glFinishFenceNV_PTR gles_glFinishFenceNV = NULL;
static glGetFenceivNV_PTR gles_glGetFenceivNV = NULL;
static glIsFenceNV_PTR gles_glIsFenceNV = NULL;

static void load_fence_funcs(void) {
    static int loaded = 0;
    if (!loaded) {
        loaded = 1; // Set first to completely block any re-entrancy
        gles_glGenFencesNV = (glGenFencesNV_PTR)dlsym(gles, "glGenFencesNV");
        gles_glDeleteFencesNV = (glDeleteFencesNV_PTR)dlsym(gles, "glDeleteFencesNV");
        gles_glSetFenceNV = (glSetFenceNV_PTR)dlsym(gles, "glSetFenceNV");
        gles_glTestFenceNV = (glTestFenceNV_PTR)dlsym(gles, "glTestFenceNV");
        gles_glFinishFenceNV = (glFinishFenceNV_PTR)dlsym(gles, "glFinishFenceNV");
        gles_glGetFenceivNV = (glGetFenceivNV_PTR)dlsym(gles, "glGetFenceivNV");
        gles_glIsFenceNV = (glIsFenceNV_PTR)dlsym(gles, "glIsFenceNV");
    }
}

EXPORT void gl4es_glGenFencesNV(GLsizei n, GLuint *fences) {
    load_fence_funcs();
    if (gles_glGenFencesNV)
        gles_glGenFencesNV(n, fences);
}

EXPORT void gl4es_glDeleteFencesNV(GLsizei n, const GLuint *fences) {
    load_fence_funcs();
    if (gles_glDeleteFencesNV)
        gles_glDeleteFencesNV(n, fences);
}

EXPORT void gl4es_glSetFenceNV(GLuint fence, GLenum condition) {
    load_fence_funcs();
    if (gles_glSetFenceNV)
        gles_glSetFenceNV(fence, condition);
}

EXPORT GLboolean gl4es_glTestFenceNV(GLuint fence) {
    load_fence_funcs();
    if (gles_glTestFenceNV)
        return gles_glTestFenceNV(fence);
    return GL_TRUE;
}

EXPORT void gl4es_glFinishFenceNV(GLuint fence) {
    load_fence_funcs();
    if (gles_glFinishFenceNV)
        gles_glFinishFenceNV(fence);
    else
        gl4es_glFinish();
}

EXPORT void gl4es_glGetFenceivNV(GLuint fence, GLenum pname, GLint *params) {
    load_fence_funcs();
    if (gles_glGetFenceivNV)
        gles_glGetFenceivNV(fence, pname, params);
}

EXPORT GLboolean gl4es_glIsFenceNV(GLuint fence) {
    load_fence_funcs();
    if (gles_glIsFenceNV)
        return gles_glIsFenceNV(fence);
    return GL_FALSE;
}
