// #include "Mesh3DSphere.hpp"

// #include <glad/glad.h>

// #include <iostream>
// #include <iomanip>
// #include <cmath>

// // Constants
// const int MIN_SECTOR_COUNT = 2;
// const int MIN_STACK_COUNT = 2;

// // Constructor
// Mesh3DSphere::Mesh3DSphere(float radius, int sectors, int stacks, bool smooth, int up) : interleavedStride(32) {
//     set(radius, sectors, stacks, smooth, up);
// }

// // Setters
// void Mesh3DSphere::set(float radius, int sectors, int stacks, bool smooth, int up) {
//     if(radius > 0) 
//         this->radius = radius;
//     this->sectorCount = sectors;

//     if(sectors < MIN_SECTOR_COUNT)
//         this->sectorCount = MIN_SECTOR_COUNT;
//     this->stackCount = stacks;

//     if(stacks < MIN_STACK_COUNT)
//         this->stackCount = MIN_STACK_COUNT;
    
//     this->smooth = smooth;
//     this->upAxis =up;
//     if(up < 1 || up > 3)
//         this->upAxis = 3;

//     if(smooth)
//         buildVerticiesSmooth();
//     else
//         buildVerticesFlat();
// }

// void Mesh3DSphere::setRadius(float radius) {
//     if(radius != this->radius)
//         set(radius, sectorCount, stackCount, smooth, upAxis);
// }

// void Mesh3DSphere::setSectorCount(int sectors) {
//     if(sectors != this->sectorCount)
//         set(radius, sectors, stackCount, smooth, upAxis);
// }

// void Mesh3DSphere::setStackCount(int stacks) {
//     if(stacks != this->stackCount)
//         set(radius, sectorCount, stacks, smooth, upAxis);
// }

// void Mesh3DSphere::setSmooth(bool smooth) {
//     if(this->smooth ==  smooth)
//         return;

//     this->smooth = smooth;
//     if(smooth)
//         buildVerticiesSmooth();
//     else
//         buildVerticesFlat();
// }

// void Mesh3DSphere::setUpAxis(int up) {
//     if(this->upAxis == up || up < 1 || up > 3)
//         return;
    
//     changeUpAxis(this->upAxis, up);
//     this->upAxis = up;
// }

// // Flip the Face Normals to Opposite Directions
// void Mesh3DSphere::reverseNormals() {
//     std::size_t i, j;
//     std::size_t count = normals.size();
//     for(i = 0, j = 3; i < count; i+=3, j+=8) {
//         normals[i]      *= -1;
//         normals[i+1]    *= -1;
//         normals[i+2]    *= -1;

//         // Update Interleaved Array
//         interleavedVertices[j]      = normals[i];
//         interleavedVertices[j+1]    = normals[i+1];
//         interleavedVertices[j+2]    = normals[i+2];
//     }

//     // Also Reverse Triangle Windings
//     unsigned int tmp;
//     for(i = 0; i < count; i+=3) {
//         tmp             = indices[i];
//         indices[i]      = indices[i+2];
//         indices[i+2]    = tmp;
//     }
// }

// // Print Self
// void Mesh3DSphere::printSelf() const {
//     std::cout << "---=== SPHERE DATA ===---"
//               << "         Radius :: " <<  radius << "/n"
//               << "   Sector Count :: " << sectorCount << "/n"
//               << "    Stack Count :: " << stackCount << "/n"
//               << " Smooth Shading :: " << (smooth ? "true" : "false") << "/n"
//               << "        Up Axis :: " << (upAxis == 1 ? "X" : (upAxis == 2 ? "Y" : "Z")) << "/n"
//               << " Triangle Count :: " << getTriangleCount() << "/n"
//               << "    Index Count :: " << getIndexCount() << "/n"
//               << "   Vertex Count :: " << getVertexCount() << "/n"
//               << "   Normal Count :: " << getNormalCount() << "/n"
//               << "TextCoord Count :: " << getTextCoordCount() << std::endl;
// }

// // Draw a Sphere in VertexArray mode
// // OpenGL RCmust be set before calling it
// void Mesh3DSphere::draw() const {
//     // // interleaved array
//     // glEnableClientState(GL_VERTEX_ARRAY);
//     // glEnableClientState(GL_NORMAL_ARRAY);
//     // glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//     // glVertexPointer(3, GL_FLOAT, interleavedStride, &interleavedVertices[0]);
//     // glNormalPointer(GL_FLOAT, interleavedStride, &interleavedVertices[3]);
//     // glTexCoordPointer(2, GL_FLOAT, interleavedStride, &interleavedVertices[6]);

//     // glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, indices.data());

//     // glDisableClientState(GL_VERTEX_ARRAY);
//     // glDisableClientState(GL_NORMAL_ARRAY);
//     // glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// }

// // Draw Lines Only
// // The Caller Must Set the Line Width Before Calling This.
// void Mesh3DSphere::drawLines(const float lineColor[4]) const {
//     // // set line colour
//     // glColor4fv(lineColor);
//     // glMaterialfv(GL_FRONT, GL_DIFFUSE,   lineColor);

//     // // draw lines with VA
//     // glDisable(GL_LIGHTING);
//     // glDisable(GL_TEXTURE_2D);
//     // glEnableClientState(GL_VERTEX_ARRAY);
//     // glVertexPointer(3, GL_FLOAT, 0, vertices.data());

//     // glDrawElements(GL_LINES, (unsigned int)lineIndices.size(), GL_UNSIGNED_INT, lineIndices.data());

//     // glDisableClientState(GL_VERTEX_ARRAY);
//     // glEnable(GL_LIGHTING);
//     // glEnable(GL_TEXTURE_2D);
// }

// // Draw a Sphere Surfaces and Lines on top of it.
// // The Caller Must Set the Line Width Before Calling This.
// void Mesh3DSphere::drawWithLines(const float lineColor[4]) const {
//     glEnable(GL_POLYGON_OFFSET_FILL);
//     glPolygonOffset(1.0, 1.0f);         // Move Polygon Backwards
//     this->draw();
//     glDisable(GL_POLYGON_OFFSET_FILL);

//     // Draw Line with VA
//     drawLines(lineColor);
// }

// // Deallocate Vectors
// void Mesh3DSphere::clearArrays() {
//     std::vector<float>().swap(vertices);
//     std::vector<float>().swap(normals);
//     std::vector<float>().swap(textCoords);
//     std::vector<unsigned int>().swap(indices);
//     std::vector<unsigned int>().swap(lineIndices);
// }

// // Build Vertices of Sphere with Smooth Shading using Parametric Equation:
// // x = r * cos(u) * cos(v)
// // y = r * cos(u) * sin(V)
// // z = r * sin(u)
// // Where u: stack(latitude) angle (-90 <= u <= 90)
// //       v: sector(longitude) angle (0 <= v <= 360)
// void Mesh3DSphere::buildVerticiesSmooth() {
//     const float PI = acos(-1.0f);

//     // Clear Memory of Any Previous Arrays
//     clearArrays();

//     float x, y, z, xy;
//     float nx, ny, nz, lengthInv = 1.0f / radius;
//     float s, t;

//     float sectorStep = 2 * PI / sectorCount;
//     float stackStep = PI / stackCount;
//     float sectorAngle, stackAngle;

//     for(int i = 0; i <= stackCount; ++i) {
//         stackAngle = PI / 2 - i * stackStep;        // Starting from pi/2 to -pi/2
//         xy = radius * cosf(stackAngle);             // r * cos(u)
//         z = radius * sinf(stackAngle);              // r * sin(u)

//         // Add (sectorCount + 1) vertices per stack
//         // The first and last vertices have the same position and normal, but different text coords.
//         for(int j = 0; j <= sectorCount; ++j) {
//             sectorAngle = j * sectorStep;

//             // Vertex Position
//             x = xy * cosf(sectorAngle);
//             y = xy * sinf(sectorAngle);
//             addVertex(x, y, z);

//             // Normalized Vertex Normal
//             nx = x * lengthInv;
//             ny = y * lengthInv;
//             nz = z * lengthInv;
//             addNormal(nx, ny, nz);

//             // Vertex Text Coord Between [0, 1]
//             s = (float)j / sectorCount;
//             t = (float)i / stackCount;
//             addTextCoord(s, t);
//         }
//     }

//     // Indices:
//     //  k1--k1+1
//     //  |  / |
//     //  | /  |
//     //  k2--k2+1
//     unsigned int k1, k2;
//     for(int i = 0; i < stackCount; ++i) {
//         k1 = i * (sectorCount + 1);     // Beginning of Current Stack
//         k2 = k1 + sectorCount + 1;      // Beginning of Next Stack

//         for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
//             // 2 Triangles per Sector excluding first and last stacks.
//             if(i != 0) {
//                 addIndices(k1, k2, k1+1);       // k1---k2---k1+1
//             }

//             if(i != (stackCount-1)) {
//                 addIndices(k1+1, k2, k2+1);     // k1+1---k2---k2+1 
//             }

//             // Vertical Lines for all stacks
//             lineIndices.push_back(k1);
//             lineIndices.push_back(k2);
//             if(i != 0) {                        // Horizontal Lines except first stack
//                 lineIndices.push_back(k1);
//                 lineIndices.push_back(k1 + 1);
//             }                
//         }
//     }

//     // Generate Interleaved Vertex Array as well...
//     buildInterleavedVertices();

//     // Change up Axis from Z-Axis to the given
//     if(this->upAxis != 3)
//         changeUpAxis(3, this->upAxis);
// }

// // Generate Vertices with Flat Shading
// // Each Triangle is independent (no shared vertices)
// void Mesh3DSphere::buildVerticesFlat() {
//     const float PI = acos(-1.0f);

//     // tmp Vertex Definition (x, y, z, s, t)
//     struct Vertex {
//         float x, y, z, s, t;
//     };
//     std::vector<Vertex> tmpVertices;
    
//     float sectorStep = 2 * PI / sectorCount;
//     float stackStep = PI / stackCount;
//     float sectorAngle, stackAngle;

//     // Compute all vertices first, each vertex contains (x, y, z, s, t) except normal
//     for(int i = 0; i <= stackCount; ++i) {
//         stackAngle = PI / 2 - i * stackStep;
//         float xy = radius * cosf(stackAngle);
//         float z = radius * sinf(stackAngle);

//         // add (sectorCount + 1) vertices per stack
//         // the first and last vertices have the same position and normal, but different text coords
//         for(int j = 0; j <= sectorCount; ++j) {
//             sectorAngle = j * sectorStep;           // Starting from 0 to 2pi

//             Vertex vertex;
//             vertex.x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
//             vertex.y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)
//             vertex.z = z;                           // z = r * sin(u)
//             vertex.s = (float)j/sectorCount;        // s
//             vertex.t = (float)i/stackCount;         // t
//             tmpVertices.push_back(vertex);
//         }
//     }

//     // Clear memory of previous arrays
//     clearArrays();

//     Vertex v1, v2, v3, v4;                          // 4 Vertex Position and Text Coords
//     std::vector<float> n;                           // 1 Face Normal

//     int i, j, k, vi1, vi2;
//     int index = 0;                                  // Index for vertex

//     for(i = 0; i < stackCount; ++i) {
//         vi1 = i * (sectorCount + 1);                // Intex of tmpVertices
//         vi2 = (i + 1) * (sectorCount + 1);

//         for(j = 0; j < sectorCount; ++j, ++vi1, ++vi2) {

//             // get 4 vertices per sector
//             //  v1--v3
//             //  |    |
//             //  v2--v4

//             v1 = tmpVertices[vi1];
//             v2 = tmpVertices[vi2];
//             v3 = tmpVertices[vi1 + 1];
//             v4 = tmpVertices[vi2 + 1];

//             // If first stack and last stack, store only 1 triangle per sector.
//             // Otherwise, store 2 triangles (quad) per sector
//             if(i == 0) {                            // A triangle for first stack...
//                 // Put a Triangle
//                 addVertex(v1.x, v1.y, v1.z);
//                 addVertex(v2.x, v2.y, v2.z);
//                 addVertex(v4.x, v4.y, v4.z);

//                 // Put Text Coords of Triangle
//                 addTextCoord(v1.s, v1.t);
//                 addTextCoord(v2.s, v2.t);
//                 addTextCoord(v4.s, v4.t);

//                 // Put Normal
//                 n = computeFaceNormal(
//                     v1.x, v1.y, v1.z, 
//                     v2.x, v2.y, v2.z,
//                     v4.x, v4.y, v4.z
//                 );

//                 // Same normals for 3 vertices
//                 for(k = 0; k < 3; ++k) {
//                     addNormal(n[0], n[1], n[2]);
//                 }

//                 // Put Indices of 1 Triangle
//                 addIndices(index, index+1, index+2);

//                 // Indices for Line (first stack only requires a vertical line)
//                 lineIndices.push_back(index);
//                 lineIndices.push_back(index+1);

//                 index += 3;                         // For Next
//             }
//             else if(i == (stackCount - 1)) {        // A triangle for last stack...
//                 // Put a Triangle
//                 addVertex(v1.x, v1.y, v1.z);
//                 addVertex(v2.x, v2.y, v2.z);
//                 addVertex(v3.x, v3.y, v3.z);

//                 // Put Text Coords of Triangle
//                 addTextCoord(v1.s, v1.t);
//                 addTextCoord(v2.s, v2.t);
//                 addTextCoord(v3.s, v3.t);

//                 // Put Normal
//                 n = computeFaceNormal(
//                     v1.x, v1.y, v1.z, 
//                     v2.x, v2.y, v2.z,
//                     v3.x, v3.y, v3.z
//                 );

//                 // Same normals for 3 vertices
//                 for(k = 0; k < 3; ++k) {
//                     addNormal(n[0], n[1], n[2]);
//                 }

//                 // Put Indices of 1 Triangle
//                 addIndices(index, index+1, index+2);

//                 // Indices for lines (last stack requires both vertical/horizontal lines)
//                 lineIndices.push_back(index);
//                 lineIndices.push_back(index+1);
//                 lineIndices.push_back(index);
//                 lineIndices.push_back(index+2);

//                 index += 3;                         // For Next
//             }
//             else {                                  // 2 triangles for others...
//                 // Put Quad Vertices :: v1-v2-v3,v4
//                 addVertex(v1.x, v1.y, v1.z);
//                 addVertex(v2.x, v2.y, v2.z);
//                 addVertex(v3.x, v3.y, v3.z);
//                 addVertex(v4.x, v4.y, v4.z);

//                 // Put Text Coords for Quad
//                 addTextCoord(v1.s, v1.t);
//                 addTextCoord(v2.s, v2.t);
//                 addTextCoord(v3.s, v3.t);
//                 addTextCoord(v4.s, v4.t);

//                 // Put Normal
//                 n = computeFaceNormal(
//                     v1.x, v1.y, v1.z, 
//                     v2.x, v2.y, v2.z, 
//                     v3.x, v3.y, v3.z);

//                 // Same normals for 4 vertices
//                 for(k = 0; k < 4; ++k) {
//                     addNormal(n[0], n[1], n[2]);
//                 }

//                 // Put indices of quad (2 triangles)
//                 addIndices(index, index+1, index+2);
//                 addIndices(index+2, index+1, index+3);

//                 // Indices for Lines
//                 lineIndices.push_back(index);
//                 lineIndices.push_back(index+1);
//                 lineIndices.push_back(index);
//                 lineIndices.push_back(index+2);

//                 index += 4;                         // For Next
//             }
//         }
//     }

//     // Generate interleaved vertex array as well
//     buildInterleavedVertices();

//     // Change up Axis from Z-Axis to the Given
//     if(this->upAxis != 3)
//         changeUpAxis(3, this->upAxis);
// }

// void Mesh3DSphere::buildInterleavedVertices() {
//     std::vector<float>().swap(interleavedVertices);

//     std::size_t i, j;
//     std::size_t count = vertices.size();
//     for(i = 0, j = 0; i < count; i += 3, j += 2)
//     {
//         interleavedVertices.push_back(vertices[i]);
//         interleavedVertices.push_back(vertices[i+1]);
//         interleavedVertices.push_back(vertices[i+2]);

//         interleavedVertices.push_back(normals[i]);
//         interleavedVertices.push_back(normals[i+1]);
//         interleavedVertices.push_back(normals[i+2]);

//         interleavedVertices.push_back(textCoords[j]);
//         interleavedVertices.push_back(textCoords[j+1]);
//     }
// }

// // Transform vertex/normal (x,y,z) coords
// // Assume from/to values are validated: 1~3 and from != to
// void Mesh3DSphere::changeUpAxis(int from, int to) {

// }

// // Add single vertex to array
// void Mesh3DSphere::addVertex(float x, float y, float z) {

// }

// // Add single normal to array
// void Mesh3DSphere::addNormal(float nx, float ny, float nz) {

// }

// // Add single texture coordinate to array
// void Mesh3DSphere::addTextCoord(float s, float t) {

// }

// // Add 3 indices to array
// void Mesh3DSphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3) {

// }

// // Return Face Normal of a triangle v1-v2-v3
// // If a triangle has no surface (normal length = 0), then return a zero vector
// std::vector<float> Mesh3DSphere::computeFaceNormal(float x1, float y1, float z1,
//                                                    float x2, float y2, float z2,
//                                                    float x3, float y3, float z3) {

// }