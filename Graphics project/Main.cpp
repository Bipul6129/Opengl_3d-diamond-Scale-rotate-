#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"

"void main()\n"
"{\n"
"   gl_Position = proj*view*model*vec4(aPos,1.0);\n"
"color = aColor;\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0f);\n"
"}\n\0";

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLfloat vertices[] =
{ //     COORDINATES     OF DIAMOND
	-0.5f, 0.0f,  0.5f,    0.1f, 0.6f,  1.0f,
	-0.5f, 0.0f, -0.5f,    0.3f, 0.0f,  0.4f,
	 0.5f, 0.0f, -0.5f,    0.9f, 1.0f,  0.3f,
	 0.5f, 0.0f,  0.5f,    1.0f, 0.1f,  0.4f,

	 0.0f, 0.8f,  0.0f,    1.0f, 1.0f,  1.3f,
	 0.0f,-0.8f,  0.0f,    0.0f, 0.0f,  0.0f,
};

	GLuint indices[] =
	{ //INDICES OF DIAMOND
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
		0,5,3,
		0,1,5,
		5,1,2,
		5,2,3,
	};


	cout << "_______Presented By_________\n ";
	cout << "Bipul,Arjal and Home\n";
	cout << "\n";
	cout << "The window will close after 6 sec automatically\n";
	
	

	bool run = true;
	while (run) {
		
		string choice;

		cout << "\n1:Scale\n";
		cout << "2:Rotate\n";
		cout << "0:exit\n";
		cout << "Your input:";
		cin >> choice;
		if (choice == "0") {
			run = false;
		}
		else if (choice == "1") {

			GLFWwindow* window = glfwCreateWindow(800, 800, "Project", NULL, NULL);
			if (window == NULL) {
				return -1;
			}

			glfwMakeContextCurrent(window);

			gladLoadGL();

			glViewport(0, 0, 800, 800);

			glfwSwapBuffers(window);

			//CREATE AND LINK SHADER FOR DIAMOND OR ANY SHAPES
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			glCompileShader(vertexShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			glCompileShader(fragmentShader);

			GLuint shaderProgram = glCreateProgram();

			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);

			glLinkProgram(shaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);



			//VAO VBO FOR THE DIAMOND
			GLuint VAO, VBO, EBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glEnable(GL_DEPTH_TEST);

			float rotation = 0.0f;
			double prevtime = glfwGetTime();
			double oldtime = glfwGetTime();
			float camera = -8.0f;
			bool increase = true;
			//THIS IS DISPLAYED ON THE WINDOW
			while (!glfwWindowShouldClose(window)) {
				glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram(shaderProgram);

				double currentTime = glfwGetTime();
				if (currentTime - prevtime >= 1 / 60) {
					rotation += 0.05f;
					if (camera >= -4.0f) {
						increase = false;
					}
					if (camera <= -8.0f) {
						increase = true;
					}
					if (increase) {
						camera += 0.004f;
						//cout << camera;
					}
					if (!increase) {
						camera -= 0.004f;
					}

					prevtime = currentTime;

				}

				glm::mat4 model = glm::mat4(1.0f);
				glm::mat4 view = glm::mat4(1.0f);
				glm::mat4 proj = glm::mat4(1.0f);
				model = glm::rotate(model, glm::radians(32.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				view = glm::translate(view, glm::vec3(0.0f, 0.0f, camera));
				proj = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);

				int modelLoc = glGetUniformLocation(shaderProgram, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				int viewLoc = glGetUniformLocation(shaderProgram, "view");
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
				int projLoc = glGetUniformLocation(shaderProgram, "proj");
				glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

				glfwSwapBuffers(window);
				glfwPollEvents();

				if (currentTime - oldtime > 7) {
					//DELETE AFTER THE USE
					glDeleteVertexArrays(1, &VAO);
					glDeleteBuffers(1, &VBO);
					glDeleteBuffers(1, &EBO);
					glDeleteProgram(shaderProgram);
					glfwDestroyWindow(window);

				}
			}
		}
		else if (choice == "2")
		{
		string axis;
		float x, y, z;
		noaxis:
		cout << "Which axis u want to rotate?\n";
		cin >> axis;
		if (axis == "x" || axis == "X") {
			x = 1.0f;
			y = 0.0f;
			z = 0.0f;
		}
		else if (axis == "y" || axis == "Y") {
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;
		}
		else if (axis == "z" || axis == "Z") {
			x = 0.0f;
			y = 0.0f;
			z = 1.0f;
		}
		else {
			cout << "\nPlease enter x y or z\n";
			goto noaxis;
		}
			GLFWwindow* window2 = glfwCreateWindow(800, 800, "Project", NULL, NULL);
			if (window2 == NULL) {
				return -1;
			}

			glfwMakeContextCurrent(window2);

			gladLoadGL();

			glViewport(0, 0, 800, 800);

			glfwSwapBuffers(window2);

			//CREATE AND LINK SHADER FOR DIAMOND OR ANY SHAPES
			GLuint vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader2, 1, &vertexShaderSource, NULL);
			glCompileShader(vertexShader2);

			GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader2, 1, &fragmentShaderSource, NULL);
			glCompileShader(fragmentShader2);

			GLuint shaderProgram2 = glCreateProgram();

			glAttachShader(shaderProgram2, vertexShader2);
			glAttachShader(shaderProgram2, fragmentShader2);

			glLinkProgram(shaderProgram2);

			glDeleteShader(vertexShader2);
			glDeleteShader(fragmentShader2);



			//VAO VBO FOR THE DIAMOND
			GLuint VAO2, VBO2, EBO2;
			glGenVertexArrays(1, &VAO2);
			glGenBuffers(1, &VBO2);
			glGenBuffers(1, &EBO2);

			glBindVertexArray(VAO2);

			glBindBuffer(GL_ARRAY_BUFFER, VBO2);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glEnable(GL_DEPTH_TEST);

			float rotation2 = 0.0f;
			double prevtime2 = glfwGetTime();
			double oldtime2 = glfwGetTime();
			float camera2 = -8.0f;
			bool increase2 = true;
			//THIS IS DISPLAYED ON THE WINDOW
			while (!glfwWindowShouldClose(window2)) {
				glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram(shaderProgram2);

				double currentTime2 = glfwGetTime();
				if (currentTime2 - prevtime2 >= 1 / 60) {
					rotation2 += 0.05f;
					if (camera2 >= -4.0f) {
						increase2 = false;
					}
					if (camera2 <= -8.0f) {
						increase2 = true;
					}
					if (increase2) {
						camera2 += 0.004f;
						//cout << camera;
					}
					if (!increase2) {
						camera2 -= 0.004f;
					}

					prevtime2 = currentTime2;

				}

				glm::mat4 model = glm::mat4(1.0f);
				glm::mat4 view = glm::mat4(1.0f);
				glm::mat4 proj = glm::mat4(1.0f);
				model = glm::rotate(model, glm::radians(rotation2), glm::vec3(x,y,z));
				view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
				proj = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);

				int modelLoc = glGetUniformLocation(shaderProgram2, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				int viewLoc = glGetUniformLocation(shaderProgram2, "view");
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
				int projLoc = glGetUniformLocation(shaderProgram2, "proj");
				glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

				glBindVertexArray(VAO2);
				glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

				glfwSwapBuffers(window2);
				glfwPollEvents();

				if (currentTime2 - oldtime2 > 7) {
					//DELETE AFTER THE USE
					glDeleteVertexArrays(1, &VAO2);
					glDeleteBuffers(1, &VBO2);
					glDeleteBuffers(1, &EBO2);
					glDeleteProgram(shaderProgram2);
					glfwDestroyWindow(window2);

				}
			}
		}else {
		cout << "\nEnter correct num\n";
         }




	}
		glfwTerminate();
		return 0;
	}
	
	

	

	