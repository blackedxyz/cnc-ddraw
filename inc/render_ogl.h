#ifndef RENDER_OGL_H
#define RENDER_OGL_H

#include <windows.h>
#include "opengl_utils.h"

#define TEXTURE_COUNT 4
#define FBO_COUNT 2

typedef struct OGLRENDERER
{
    HGLRC context;
    GLuint main_program;
    GLuint shader1_program;
    GLuint shader2_program;
    BOOL got_error;
    int surface_tex_width;
    int surface_tex_height;
    int* surface_tex;
    GLenum surface_format;
    GLenum surface_type;
    GLuint surface_tex_ids[TEXTURE_COUNT];
    GLuint palette_tex_ids[TEXTURE_COUNT];
    float scale_w;
    float scale_h;
    GLint main_tex_coord_attr_loc;
    GLint main_vertex_coord_attr_loc;
    GLuint main_vbos[3];
    GLuint main_vao;
    GLint frame_count_uni_loc;
    GLuint frame_buffer_id[FBO_COUNT];
    GLuint frame_buffer_tex_id[FBO_COUNT];
    GLint shader1_tex_coord_attr_loc;
    GLint shader2_tex_coord_attr_loc;
    GLuint shader1_vbos[3];
    GLuint shader2_vbos[3];
    GLuint shader1_vao;
    GLuint shader2_vao;
    BOOL use_opengl;
    BOOL filter_bilinear;
    BOOL shader2_upscale;
} OGLRENDERER;

DWORD WINAPI ogl_render_main(void);

#endif
