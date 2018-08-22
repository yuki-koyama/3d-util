#ifndef GL_WRAPPER_HPP
#define GL_WRAPPER_HPP

#include <three-dim-util/gl.hpp>
#include <Eigen/Core>

namespace threedimutil
{
    inline void clear_color_3d(const Eigen::Vector3d& c) { glClearColor(c(0), c(1), c(2), 1.0); }
    inline void color_3d(const Eigen::Vector3d& c) { glColor3d(c(0), c(1), c(2)); }
    inline void color_4d(const Eigen::Vector3d& c, double a) { glColor4d(c(0), c(1), c(2), a); }
    
    inline void vertex_2d(const Eigen::Vector2d& v) { glVertex2d(v(0), v(1)); }
    inline void vertex_3d(const Eigen::Vector3d& v) { glVertex3d(v(0), v(1), v(2)); }

    inline void translate(const Eigen::Vector3d& t) { glTranslated(t(0), t(1), t(2)); }
    inline void rotate(double angle, const Eigen::Vector3d& axis) { glRotated(angle, axis(0), axis(1), axis(2)); }
    
    inline void load_matrix(const Eigen::Matrix4d& m) { glLoadMatrixd(m.data()); }
    inline void mult_matrix(const Eigen::Matrix4d& m) { glMultMatrixd(m.data()); }
    
    inline void read_pixels(int width,
                            int height,
                            Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& R,
                            Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& G,
                            Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& B,
                            Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& A)
    {
        Eigen::Matrix<GLuint, Eigen::Dynamic, Eigen::Dynamic> buffer(width, height);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());
        R = Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>(width, height);
        G = Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>(width, height);
        B = Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>(width, height);
        A = Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>(width, height);
        for (int x = 0; x < width; ++ x)
        {
            for (int y = 0; y < height; ++ y)
            {
                R(x, y) = (buffer(x, y) & 0xff000000) >> 24;
                G(x, y) = (buffer(x, y) & 0x00ff0000) >> 16;
                B(x, y) = (buffer(x, y) & 0x0000ff00) >> 8;
                A(x, y) = (buffer(x, y) & 0x000000ff) >> 0;
            }
        }
    }
}

#endif // GL_WRAPPER_HPP
