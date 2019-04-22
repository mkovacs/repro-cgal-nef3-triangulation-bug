#include <cmath>
#include <sstream>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/boost/graph/convert_nef_polyhedron_to_polygon_mesh.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3> Surface_mesh;
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron_3;
typedef Nef_polyhedron_3::Vector_3 Vector_3;
typedef Kernel::Point_3 Point_3;
typedef Nef_polyhedron_3::Aff_transformation_3 Aff_transformation_3;

Aff_transformation_3 make_rotation(double x, double y, double z, double angle) {
    double len = std::sqrt(x*x + y*y + z*z);
    x /= len;
    y /= len;
    z /= len;
    double c = std::cos(angle);
    double s = std::sin(angle);
    double m = 1.0 - c;
    return Aff_transformation_3(
            c + x*x*m, x*y*m - z*s, x*z*m + y*s,
            y*x*m + z*s, c + y*y*m, y*z*m - x*s,
            z*x*m - y*s, z*y*m + x*s, c + z*z*m);
}

int main() {
    std::stringstream input_stream("OFF\n\
8 12 0\n\
-1 -1 -1\n\
-1 1 -1\n\
1 1 -1\n\
1 -1 -1\n\
-1 -1 1\n\
-1 1 1\n\
1 1 1\n\
1 -1 1\n\
3  0 1 3\n\
3  3 1 2\n\
3  0 4 1\n\
3  1 4 5\n\
3  3 2 7\n\
3  7 2 6\n\
3  4 0 3\n\
3  7 4 3\n\
3  6 4 7\n\
3  6 5 4\n\
3  1 5 6\n\
3  2 1 6");
    Surface_mesh cube_surface;
    input_stream >> cube_surface;
    Nef_polyhedron_3 cube(cube_surface);

    Aff_transformation_3 translate(CGAL::TRANSLATION, Vector_3(1.0, 1.0, 1.0));
    Aff_transformation_3 rotate = make_rotation(1.0, 1.0, 1.0, 1.5);

    Nef_polyhedron_3 other_cube = cube;
    other_cube.transform(translate * rotate);
    Nef_polyhedron_3 result = cube.difference(other_cube);

    Surface_mesh result_surface;
    CGAL::convert_nef_polyhedron_to_polygon_mesh<Nef_polyhedron_3, Surface_mesh>(result, result_surface, true);

    CGAL::write_off(std::cout, result_surface);
    std::cout << "# is_simple: " << result.is_simple() << std::endl;
}
