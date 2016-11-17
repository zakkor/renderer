#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct shader {
    GLuint program;
} shader;

shader shader_new(const char vertex_path[], const char fragment_path[]) {
    GLchar * buffers[2] = {};

    long length = 0;
    FILE * files[2] = {};
    files[0] = fopen(vertex_path, "rb");
    files[1] = fopen(fragment_path, "rb");

    if (files[0] && files[1]) {
        for (int i = 0; i <= 1; i++) {
            fseek(files[i], 0, SEEK_END);
            length = ftell(files[i]);
            fseek(files[i], 0, SEEK_SET);

            buffers[i] = malloc(length + 1);

            if (buffers[i])
            {
                fread(buffers[i], 1, length, files[i]);
            }

            buffers[i][length] = '\0';

            fclose(files[i]);
        }
    } else {
        perror("Error when reading shader files");
    }

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &buffers[0], NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        // TODO: error!
    };


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &buffers[1], NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        // TODO: error!
    };

    shader s;
    s.program = glCreateProgram();
    glAttachShader(s.program, vertex);
    glAttachShader(s.program, fragment);
    glLinkProgram(s.program);

    glGetProgramiv(s.program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(s.program, 512, NULL, infoLog);
        // TODO: error!
    }

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // free files
    free(buffers[0]);
    free(buffers[1]);

    return s;
}

void shader_use(shader *s) {
    glUseProgram(s->program);
}

#endif
