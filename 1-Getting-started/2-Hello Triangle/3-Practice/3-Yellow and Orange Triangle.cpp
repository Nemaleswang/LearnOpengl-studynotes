#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"//声明版本和使用核心模式，因为用的是opengl3.3版本
"layout(location = 0) in vec3 aPos;\n"//vec3代表包含3个float数据的向量
"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"//将位置数据赋给gl_position
"}\0";

const char *fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"//定义一个输出变量为4分量变量
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char *fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"//定义一个输出变量为4分量变量
"void main(){\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
    
void framebuffer_size_callback(GLFWwindow* window, int width, int height){//回调函数
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window){ 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //检测ESC键是否按下，按下则将WindowShouldClose属性置为true
		glfwSetWindowShouldClose(window, true);
}

int main(){
	glfwInit();//初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//指定主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//指定次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL,NULL);//高度，宽度，窗口名
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数，窗口调整大小时条用该函数

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//glViewport(0, 0, 800, 600);//左下角位置，宽度，高度

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建一个顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//将着色器源码附着到着色器对象上
	glCompileShader(vertexShader);//编译着色器对象

	unsigned int fragmentShaderOrange;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);//创建一个片段着色器
	glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);//将着色器源码附着到着色器对象上
	glCompileShader(fragmentShaderOrange);//编译着色器对象

	unsigned int fragmentShaderYellow;
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);//创建一个片段着色器
	glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);//将着色器源码附着到着色器对象上
	glCompileShader(fragmentShaderYellow);//编译着色器对象

	unsigned int shaderProgramOrange;
	shaderProgramOrange = glCreateProgram();//创建一个着色器程序
	unsigned int shaderProgramYellow;
	shaderProgramYellow = glCreateProgram();//创建一个着色器程序

	glAttachShader(shaderProgramOrange, vertexShader);//将编译好的着色器附加到程序对象上
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);//链接它们

	glAttachShader(shaderProgramYellow, vertexShader);//将编译好的着色器附加到程序对象上
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);//链接它们

	
	float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};

	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	//0、赋值顶点数据到缓冲中供OpenGL使用
	unsigned int VBOs[2],VAOs[2];//需要生成一个VBO对象
	glGenVertexArrays(2, VAOs);//用函数和缓冲ID生成VAO对象
	glGenBuffers(2, VBOs);//用函数和缓冲ID生成VBO对象
	glBindVertexArray(VAOs[0]);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);//将新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);//将顶点数据放入缓冲的内存中

	//1、设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGLe如何解析顶点数据
	//五个属性分别：配置的顶点位置属性、顶点属性的大小，vec3、顶点数据类型、数据是否标准化、步长、偏移量
	glEnableVertexAttribArray(0);//启用顶点属性

	glBindVertexArray(VAOs[1]);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//将新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);//将顶点数据放入缓冲的内存中

	//1、设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGLe如何解析顶点数据
	//五个属性分别：配置的顶点位置属性、顶点属性的大小，vec3、顶点数据类型、数据是否标准化、步长、偏移量
	glEnableVertexAttribArray(0);//调用与顶点属性关联的顶点缓冲对象

	while (!glfwWindowShouldClose(window)){//检查glfw是否要求被退出
		processInput(window);//每次检测是否ESC键按下

		glClearColor(0.2f,0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramOrange);//激活该函数对象，现在顶点数据已经发送给了GPU
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);//绘制三角形

		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);//绘制三角形

		glfwSwapBuffers(window);//交换颜色缓冲，使用双缓冲
		glfwPollEvents();//检查是否有触发事件
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;
}