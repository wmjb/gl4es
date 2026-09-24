#ifndef _GL4ES_FENCE_H_
#define _GL4ES_FENCE_H_

#include "gl4es.h"

EXPORT void gl4es_glGenFencesNV(GLsizei n, GLuint *fences);
EXPORT void gl4es_glDeleteFencesNV(GLsizei n, const GLuint *fences);
EXPORT void gl4es_glSetFenceNV(GLuint fence, GLenum condition);
EXPORT GLboolean gl4es_glTestFenceNV(GLuint fence);
EXPORT void gl4es_glFinishFenceNV(GLuint fence);
EXPORT void gl4es_glGetFenceivNV(GLuint fence, GLenum pname, GLint *params);
EXPORT GLboolean gl4es_glIsFenceNV(GLuint fence);

#endif
