//���������
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


//float pitch = 0, yaw = -90.0f;
//float fov = 45.0f;

//�̶���ת90�Ȳ�����0.5��
    /*glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 0, 1));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));*/

    //һֱ��ת��2D����
    /*glm::mat4 trans;
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));*/


    //����3D����
    //glm::mat4 model = glm::mat4(1.0f);
    //����ʱ����ת
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //glm::mat4 view = glm::mat4(1.0f);
    // ע�⣬���ǽ�����������Ҫ�����ƶ������ķ������ƶ���
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


        /*int modelLoc = glGetUniformLocation(ourshader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));*/
        //int viewLoc = glGetUniformLocation(ourshader.ID, "view");
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        //int projectionLoc = glGetUniformLocation(ourshader.ID, "projection");
        //glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        /*unsigned int transformLoc = glGetUniformLocation(ourshader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/

        //uniform����
        /*float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

        //float offsetValue = 0.3f;
        /*int vertexColorLocation = glGetUniformLocation(ourshader.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
        //ourshader.setFloat("offset", offsetValue);


        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

       // glDrawArrays(GL_TRIANGLES, 0, 36);

        //��ԭ����ת�������
        //float radius = 10.0f;
        //float camX = sin(glfwGetTime()) * radius;
        //float camZ = cos(glfwGetTime()) * radius;
        //glm::mat4 view;
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //ourshader.setMat4("view", view);

        //�����ƶ��������
        /*glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourshader.setMat4("view", view);*/


        //����10��������
                //for (unsigned int i = 0; i < 10; i++)
                //{
                //    glm::mat4 model = glm::mat4(1.0f);
                //    model = glm::translate(model, cubePositions[i]);
                //    float angle = 20.0f * i;
                //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                //    ourshader.setMat4("model", model);

                //    glDrawArrays(GL_TRIANGLES, 0, 36);
                //}
                //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                // glBindVertexArray(0); // no need to unbind it every time 