FILES=example_square.cpp elgarenta.cpp imgui/imgui_draw.cpp imgui/imgui.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp
LIBRARIES=-lGL -lglfw -lpthread
OUTPUT=example_square.out
INCLUDE=-I./imgui -I./
DSO=-ldl
SETTINGS=-O0 -g

all: clean
	g++ ${FILES} ${LIBRARIES} ${DSO} ${SETTINGS} ${INCLUDE} -o ${OUTPUT}
clean:
	rm -rfv ${OUTPUT}