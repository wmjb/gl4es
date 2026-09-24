#ifndef _GL4ES_OCCLUSION_H_
#define _GL4ES_OCCLUSION_H_

#include "gl4es.h"

EXPORT void gl4es_glGenQueriesARB(GLsizei n, GLuint *ids);
EXPORT void gl4es_glDeleteQueriesARB(GLsizei n, const GLuint *ids);
EXPORT GLboolean gl4es_glIsQueryARB(GLuint id);
EXPORT void gl4es_glBeginQueryARB(GLenum target, GLuint id);
EXPORT void gl4es_glEndQueryARB(GLenum target);
EXPORT void gl4es_glGetQueryObjectivARB(GLuint id, GLenum pname, GLint *params);
EXPORT void gl4es_glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint *params);

#endif
