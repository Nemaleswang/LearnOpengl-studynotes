#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"//�����汾��ʹ�ú���ģʽ����Ϊ�õ���opengl3.3�汾
"layout(location = 0) in vec3 position;\n"//vec3�������3��float���ݵ�����
"layout(location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main(){\n"
"gl_Position = vec4(position, 1.0);\n"//��λ�����ݸ���gl_position
"ourColor = color;\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"//����һ���������Ϊ4��������
"void main(){\n"
"color = vec4(ourColor,1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height){//�ص�����
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //���ESC���Ƿ��£�������WindowShouldClose������Ϊtrue
		glfwSetWindowShouldClose(window, true);
}

int main(){
	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//ָ�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//ָ���ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//�߶ȣ���ȣ�������
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע��ص����������ڵ�����Сʱ���øú���

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//glViewport(0, 0, 800, 600);//���½�λ�ã���ȣ��߶�

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//����һ��������ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//����ɫ��Դ�븽�ŵ���ɫ��������
	glCompileShader(vertexShader);//������ɫ������

	/*��ⶥ����ɫ���Ƿ����ɹ�*/
	int success;
	char infoLog[512];//�洢������Ϣ������
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//��������ȡ������Ϣ����ӡ
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//����һ��Ƭ����ɫ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//����ɫ��Դ�븽�ŵ���ɫ��������
	glCompileShader(fragmentShader);//������ɫ������

	/*���Ƭ����ɫ���Ƿ����ɹ�*/
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);//��������ȡ������Ϣ����ӡ
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();//����һ����ɫ������
	glAttachShader(shaderProgram, vertexShader);//������õ���ɫ�����ӵ����������
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);//��������

	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);//���������ɫ�������Ƿ����
	if (!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);//��ȡ������Ϣ
	}

	glDeleteShader(vertexShader);//ɾ����ɫ������
	glDeleteShader(fragmentShader);

	float vertices[] = { //z����ȫ������Ϊ��
		//λ��				//��ɫ
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // ����
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // ����
	};

	//0����ֵ�������ݵ������й�OpenGLʹ��
	unsigned int VBO, VAO;//��Ҫ����һ��VBO����
	glGenVertexArrays(1, &VAO);//��VAO
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);//��VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���������ݷ��뻺����ڴ���


	//1�����ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//����OpenGLe��ν�����������
	//������Էֱ����õĶ���λ�����ԡ��������ԵĴ�С��vec3�������������͡������Ƿ��׼����������ƫ����
	glEnableVertexAttribArray(0);

	//1��������ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));//����OpenGLe��ν�����������
	//������Էֱ����õ���ɫλ�����ԡ��������ԵĴ�С��vec3�������������͡������Ƿ��׼����������ƫ����
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)){//���glfw�Ƿ�Ҫ���˳�
		processInput(window);//ÿ�μ���Ƿ�ESC������

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);//����ú����������ڶ��������Ѿ����͸���GPU

		GLfloat timeValue = glfwGetTime();//��ȡ��������
		GLfloat greenValue = sin(timeValue) / 2.0f + 0.5f;//��sin��������ɫ��0.0��1.0�ı�
		//��ѯuniform ourcolor��λ�ã��ṩ��ɫ�������uniform������
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//����uniform��ֵ������uniform֮ǰ��Ҫʹ�ó���
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);//����һ�������Σ���ʵ����Ϊ�㣬������Ϊ3

		glfwSwapBuffers(window);//������ɫ���壬ʹ��˫����
		glfwPollEvents();//����Ƿ��д����¼�
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}