#include "gl4es.h"
#include "loader.h"
#include <dlfcn.h>

extern void *gles;

// Define function pointers for the underlying GLES EXT occlusion queries
typedef void (*glGenQueriesEXT_PTR)(GLsizei n, GLuint *ids);
typedef void (*glDeleteQueriesEXT_PTR)(GLsizei n, const GLuint *ids);
typedef GLboolean (*glIsQueryEXT_PTR)(GLuint id);
typedef void (*glBeginQueryEXT_PTR)(GLenum target, GLuint id);
typedef void (*glEndQueryEXT_PTR)(GLenum target);
typedef void (*glGetQueryObjectivEXT_PTR)(GLuint id, GLenum pname, GLint *params);
typedef void (*glGetQueryObjectuivEXT_PTR)(GLuint id, GLenum pname, GLuint *params);

static glGenQueriesEXT_PTR gles_glGenQueriesEXT = NULL;
static glDeleteQueriesEXT_PTR gles_glDeleteQueriesEXT = NULL;
static glIsQueryEXT_PTR gles_glIsQueryEXT = NULL;
static glBeginQueryEXT_PTR gles_glBeginQueryEXT = NULL;
static glEndQueryEXT_PTR gles_glEndQueryEXT = NULL;
static glGetQueryObjectivEXT_PTR gles_glGetQueryObjectivEXT = NULL;
static glGetQueryObjectuivEXT_PTR gles_glGetQueryObjectuivEXT = NULL;

static void load_occlusion_funcs(void) {
    static int loaded = 0;
    if (!loaded) {
        loaded = 1; // Set FIRST to block any re-entrant recursion

        gles_glGenQueriesEXT = (glGenQueriesEXT_PTR)dlsym(gles, "glGenQueriesEXT");
        gles_glDeleteQueriesEXT = (glDeleteQueriesEXT_PTR)dlsym(gles, "glDeleteQueriesEXT");
        gles_glIsQueryEXT = (glIsQueryEXT_PTR)dlsym(gles, "glIsQueryEXT");
        gles_glBeginQueryEXT = (glBeginQueryEXT_PTR)dlsym(gles, "glBeginQueryEXT");
        gles_glEndQueryEXT = (glEndQueryEXT_PTR)dlsym(gles, "glEndQueryEXT");
        gles_glGetQueryObjectivEXT = (glGetQueryObjectivEXT_PTR)dlsym(gles, "glGetQueryObjectivEXT");
        gles_glGetQueryObjectuivEXT = (glGetQueryObjectuivEXT_PTR)dlsym(gles, "glGetQueryObjectuivEXT");
    }
}

EXPORT void gl4es_glGenQueriesARB(GLsizei n, GLuint *ids) {
    load_occlusion_funcs();
    if (gles_glGenQueriesEXT) {
        gles_glGenQueriesEXT(n, ids);
    }
}

EXPORT void gl4es_glDeleteQueriesARB(GLsizei n, const GLuint *ids) {
    load_occlusion_funcs();
    if (gles_glDeleteQueriesEXT) {
        gles_glDeleteQueriesEXT(n, ids);
    }
}

EXPORT GLboolean gl4es_glIsQueryARB(GLuint id) {
    load_occlusion_funcs();
    if (gles_glIsQueryEXT) {
        return gles_glIsQueryEXT(id);
    }
    return GL_FALSE;
}

EXPORT void gl4es_glBeginQueryARB(GLenum target, GLuint id) {
    load_occlusion_funcs();
    if (gles_glBeginQueryEXT) {
        // Map ARB targets to EXT targets if needed
        GLenum es_target = target;
        if (target == 0x8892 || target == 0x8C47) { // GL_SAMPLES_PASSED / GL_ANY_SAMPLES_PASSED
            es_target = 0x8D52; // GL_ANY_SAMPLES_PASSED_EXT
        }
        gles_glBeginQueryEXT(es_target, id);
    }
}

EXPORT void gl4es_glEndQueryARB(GLenum target) {
    load_occlusion_funcs();
    if (gles_glEndQueryEXT) {
        GLenum es_target = target;
        if (target == 0x8892 || target == 0x8C47) {
            es_target = 0x8D52;
        }
        gles_glEndQueryEXT(es_target);
    }
}

EXPORT void gl4es_glGetQueryObjectivARB(GLuint id, GLenum pname, GLint *params) {
    load_occlusion_funcs();
    if (gles_glGetQueryObjectivEXT) {
        gles_glGetQueryObjectivEXT(id, pname, params);
    } else if (gles_glGetQueryObjectuivEXT) {
        GLuint val = 0;
        gles_glGetQueryObjectuivEXT(id, pname, &val);
        *params = (GLint)val;
    }
}

EXPORT void gl4es_glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint *params) {
    load_occlusion_funcs();
    if (gles_glGetQueryObjectuivEXT) {
        gles_glGetQueryObjectuivEXT(id, pname, params);
    } else if (gles_glGetQueryObjectivEXT) {
        GLint val = 0;
        gles_glGetQueryObjectivEXT(id, pname, &val);
        *params = (GLuint)val;
    }
}
