#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int VBO;//需要生成一个VBO对象
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);//将新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	

	glViewport(0, 0, 800, 600);//左下角位置，宽度，高度
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数，窗口调整大小时条用该函数

	while (!glfwWindowShouldClose(window)){//检查glfw是否要求被退出
		processInput(window);//每次检测是否ESC键按下

		glad_glClearColor(0.2f,0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);//交换颜色缓冲，使用双缓冲
		glfwPollEvents();//检查是否有触发事件
	}
	glfwTerminate();
	return 0;
}