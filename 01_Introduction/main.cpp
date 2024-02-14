// GLEW
// 包含glew.h头文件时会引入许多OpenGL必要的头文件(例如GL/gl.h)
// 所以#include <GL/glew.h>应放在引入其他头文件的代码之前
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	glfwInit();

	// Settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	

	// GLFW
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Viewport
	glViewport(0, 0, 800, 600);


	// Callback Function
	glfwSetKeyCallback(window, key_callback);

	// Vertex Data
	//GLfloat vertices[] = {
	//	0.5f, 0.5f, 0.0f, // 右上角
	//	0.5f, -0.5f, 0.0f, // 右下角
	//	-0.5f, -0.5f, 0.0f, // 左下角
	//	-0.5f, 0.5f, 0.0f // 左上角
	//};

	GLfloat vertices[] = {
		// 位置 // 颜色
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右下
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // 顶部
	};

	GLuint indices[] = { // 起始于0!
		0, 1, 3, // 第一个三角形
		1, 2, 3 // 第二个三角形
	};


	// Shader
	const GLchar* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position.x, position.y, position.z, 1.0); \n"
		"	ourColor = color;\n"
		"}\n";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 color;\n"
		//"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(ourColor, 1.0f);\n"
		"}\n";
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Link Vertex Attribute
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	// GL_ELEMENT_ARRAY_BUFFER
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// glVertexAttribPointer Parameters:
	// 1. location
	// 2. 顶点属性大小，由于是vec3，由3个数组成
	// 3. 数据类型
	// 4. 是否希望被标准化
	// 5. stride
	// 6. 在buffer中起始位置的偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	// 开启顶点属性，location为参数
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);	// 解绑VAO

	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();


		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		*/
		glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// 线框模式
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}


	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}