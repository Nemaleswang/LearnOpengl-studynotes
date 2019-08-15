#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"//�����汾��ʹ�ú���ģʽ����Ϊ�õ���opengl3.3�汾
"layout(location = 0) in vec3 aPos;\n"//vec3��������3��float���ݵ�����
"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"//��λ�����ݸ���gl_position
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"//����һ���������Ϊ4��������
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//ָ�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//ָ���ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL,NULL);//�߶ȣ����ȣ�������
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

	//glViewport(0, 0, 800, 600);//���½�λ�ã����ȣ��߶�

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

	//0����ֵ�������ݵ������й�OpenGLʹ��
	unsigned int VBOs[2],VAOs[2];//��Ҫ����һ��VBO����
	glGenVertexArrays(2, VAOs);//�ú����ͻ���ID����VAO����
	glGenBuffers(2, VBOs);//�ú����ͻ���ID����VBO����
	glBindVertexArray(VAOs[0]);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);//���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);//���������ݷ��뻺����ڴ���

	//1�����ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//����OpenGLe��ν�����������
	//������Էֱ����õĶ���λ�����ԡ��������ԵĴ�С��vec3�������������͡������Ƿ��׼����������ƫ����
	glEnableVertexAttribArray(0);//���ö�������

	glBindVertexArray(VAOs[1]);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);//���������ݷ��뻺����ڴ���

	//1�����ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//����OpenGLe��ν�����������
	//������Էֱ����õĶ���λ�����ԡ��������ԵĴ�С��vec3�������������͡������Ƿ��׼����������ƫ����
	glEnableVertexAttribArray(0);//�����붥�����Թ����Ķ��㻺�����

	while (!glfwWindowShouldClose(window)){//���glfw�Ƿ�Ҫ���˳�
		processInput(window);//ÿ�μ���Ƿ�ESC������

		glClearColor(0.2f,0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);//����ú����������ڶ��������Ѿ����͸���GPU
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);//����������

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);//����������

		glfwSwapBuffers(window);//������ɫ���壬ʹ��˫����
		glfwPollEvents();//����Ƿ��д����¼�
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;
}