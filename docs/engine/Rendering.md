# Rendering

For each vertex you want to display, you create a vertex buffer object (VBO) with info about that vertex like color and coordinates.

This is not required, but to diplay a batch of vertex buffers at once instead of one at a time, you can use a vertex array object (VAO) and element array buffer object (EBO) to do this quickly. The VAO contains all the VBOs, and the EBO tells openGL where the indices for each primitive are, in the array of verticecs.

Everything is made up of triangles. A rectangle, for example, is just 2 triangles.
