#include "SpriteSurface.h"
#include "../../Graphics/ShaderHandler.h"

SpriteSurface::SpriteSurface(std::string imageLoader_, glm::vec2 imageScaler_, float angle_, glm::vec4 tintColour_) : VAO(0), VBO(0), modelLoc(0), projLoc(0), colourLoc(0), textureLoc(0) {

    vertexList.push_back(Vertex2D(glm::vec2(-0.5f, 0.5f), glm::vec2(0.0f, 0.0f)));
    vertexList.push_back(Vertex2D(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 0.0f)));
    vertexList.push_back(Vertex2D(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f)));
    vertexList.push_back(Vertex2D(glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 1.0f)));

    imageScaler = glm::vec2(imageScaler_);
    angle = angle_;
    tintColour = tintColour_;

    if (imageLoader_ != "") {
        imageLoader = imageLoader_;
    }

   if (TextureHandler::GetInstance()->GetTexture(imageLoader) == 0) {
       TextureHandler::GetInstance()->CreateTexture(imageLoader, "./Resources/Textures/" + imageLoader + ".png");
   }

   textureID = TextureHandler::GetInstance()->GetTexture(imageLoader);
   width = TextureHandler::GetInstance()->GetTextureData(imageLoader)->width;
   height = TextureHandler::GetInstance()->GetTextureData(imageLoader)->height;

   GenerateBuffers();
}

SpriteSurface::~SpriteSurface() {
    vertexList.clear();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SpriteSurface::DrawSurface(Camera* camera_, glm::vec2 position_) {
    glUniform1d(textureLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position_.x, position_.y, 0));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(width * imageScaler.x, height * imageScaler.y, 1.0f));
    glUniform4fv(colourLoc, 1, glm::value_ptr(glm::vec4(tintColour.r, tintColour.g, tintColour.b, tintColour.a)));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

float SpriteSurface::GetWidth() {
    return width;
}

float SpriteSurface::GetHeight() {
    return height;
}

void SpriteSurface::GenerateBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);

    //Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

    //Texture Coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, spriteTextureCoords));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    spriteShaderProgram = ShaderHandler::GetInstance()->GetShader("GUIShader");

    modelLoc = glGetUniformLocation(spriteShaderProgram, "model");
    projLoc = glGetUniformLocation(spriteShaderProgram, "proj");
    textureLoc = glGetUniformLocation(spriteShaderProgram, "inputTexture");
    colourLoc = glGetUniformLocation(spriteShaderProgram, "tintColour");
}