#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){//�ص�����
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window){ 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //���ESC���Ƿ��£�������WindowShouldClose������Ϊtrue
		glfwSetWindowShouldClose(window, true);
}

int main(){
	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//ָ�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//ָ���ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL,NULL);//�߶ȣ���ȣ�������
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

	unsigned int VBO;//��Ҫ����һ��VBO����
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);//���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	

	glViewport(0, 0, 800, 600);//���½�λ�ã���ȣ��߶�
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע��ص����������ڵ�����Сʱ���øú���

	while (!glfwWindowShouldClose(window)){//���glfw�Ƿ�Ҫ���˳�
		processInput(window);//ÿ�μ���Ƿ�ESC������

		glad_glClearColor(0.2f,0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);//������ɫ���壬ʹ��˫����
		glfwPollEvents();//����Ƿ��д����¼�
	}
	glfwTerminate();
	return 0;
}