#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"//声明版本和使用核心模式，因为用的是opengl3.3版本
"layout(location = 0) in vec3 aPos;\n"//vec3代表包含3个float数据的向量
"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"//将位置数据赋给gl_position
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"//定义一个输出变量为4分量变量
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

	/*检测顶点着色器是否编译成功*/
	int success;
	char infoLog[512];//存储错误消息的容器
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//编译错误获取错误消息并打印
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建一个片段着色器
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//将着色器源码附着到着色器对象上
	glCompileShader(fragmentShader);//编译着色器对象

	/*检测片段着色器是否编译成功*/
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);//编译错误获取错误消息并打印
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();//创建一个着色器程序
	glAttachShader(shaderProgram, vertexShader);//将编译好的着色器附加到程序对象上
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);//链接它们

	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);//检查连接着色器程序是否出错
	if (!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);//获取错误信息
	}

	glDeleteShader(vertexShader);//删除着色器对象
	glDeleteShader(fragmentShader);

	float vertices[] = { //z坐标全部定义为零
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//0、赋值顶点数据到缓冲中供OpenGL使用
	unsigned int VBO,VAO;//需要生成一个VBO对象
	glGenVertexArrays(1, &VAO);//绑定VAO
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);//绑定VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将顶点数据放入缓冲的内存中
	

	//1、设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGLe如何解析顶点数据
	//五个属性分别：配置的顶点位置属性、顶点属性的大小，vec3、顶点数据类型、数据是否标准化、步长、偏移量
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)){//检查glfw是否要求被退出
		processInput(window);//每次检测是否ESC键按下

		glClearColor(0.2f,0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);//激活该函数对象，现在顶点数据已经发送给了GPU
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);//绘制一个三角形，其实索引为零，顶点数为3

		glfwSwapBuffers(window);//交换颜色缓冲，使用双缓冲
		glfwPollEvents();//检查是否有触发事件
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}