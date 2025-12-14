#ifndef MESH3DSPHERE_HPP
#define MESH3DSPHERE_HPP

#include <vector>

class Mesh3DSphere {
    public:

        // Constructor
        Mesh3DSphere(
            float radius = 1.0f, 
            int sectorCount = 36, 
            int stackCount = 18, 
            bool smooth = true, 
            int up = 3);

        // Destructor
        ~Mesh3DSphere() {}

        // Getters
        float getRadius() const                 { return radius; }
        int getSectorCount() const              { return sectorCount; }
        int getStackCount() const               { return stackCount; }
        int getUpAxis() const                   { return upAxis; }

        // Setters
        void set(
            float radius, 
            int sectorCount, 
            int stackCount, 
            bool smooth=true, 
            int up = 3);
        void setRadius(float radius);
        void setSectorCount(int sectorCount);
        void setStackCount(int stackCount);
        void setSmooth(bool smooth);
        void setUpAxis(int up);
        void reverseNormals();

        // For Vertex Data
        unsigned int getVertexCount() const         { return (unsigned int)vertices.size() / 3; }
        unsigned int getNormalCount() const         { return (unsigned int)normals.size() / 3; }
        unsigned int getTextCoordCount() const      { return (unsigned int)textCoords.size() / 2; }
        unsigned int getIndexCount() const          { return (unsigned int)indices.size(); }
        unsigned int getLineIndexCount() const      { return (unsigned int)lineIndices.size(); }
        unsigned int getTriangleCount() const       { return getIndexCount() / 3; }
        unsigned int getVertexSize() const          { return (unsigned int)vertices.size() * sizeof(float); }
        unsigned int getNormalsSize() const         { return (unsigned int)normals.size() * sizeof(float); }
        unsigned int getTextCoordSize() const       { return (unsigned int)textCoords.size() * sizeof(float); }
        unsigned int getIndexSize() const           { return (unsigned int)indices.size() * sizeof(float); }
        unsigned int getLineIndexSize() const       { return (unsigned int)lineIndices.size() * sizeof(float); }

        const float* getVertices() const            { return vertices.data(); }
        const float* getNormals() const             { return normals.data(); }
        const float* getTextCoords() const          { return textCoords.data(); }

        const unsigned int* getIndices() const      { return indices.data(); }
        const unsigned int* getLineIndices() const  { return lineIndices.data(); }
        
        // For Interleaved Vertices: V/N/T
        unsigned int getInterleavedVertexCount() const  { return getVertexCount(); }
        unsigned int getInterleavedVertexSize() const   { return (unsigned int)interleavedVertices.size() * sizeof(float); }
        int getInterleavedStride() const                { return interleavedStride; }
        const float* getInterleavedVertices() const     { return interleavedVertices.data(); }

        // Draw in VertexArray Mode
        void draw() const;                                      // draw surface
        void drawLines(const float lineColor[4]) const;         // draw lines only
        void drawWithLines(const float lineColor[4]) const;     // draw surfaceand lines

        // Debug
        void printSelf() const;

    protected:

    private:
        // Member Functions
        void buildVerticiesSmooth();
        void buildVerticesFlat();
        void buildInterleavedVertices();
        void changeUpAxis(int from, int to);
        void clearArrays();
        void addVertex(float x, float y, float z);
        void addNormal(float x, float y, float z);
        void addTextCoord(float s, float t);
        void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
        std::vector<float> computeFaceNormal(float x1, float y1, float z1,
                                            float x2, float y2, float z2,
                                            float x3, float y3, float z3);

        // Member Variables
        float radius;
        int sectorCount;
        int stackCount;
        bool smooth;
        int upAxis;
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> textCoords;
        std::vector<unsigned int> indices;
        std::vector<unsigned int> lineIndices;

        // Interleaved
        std::vector<float> interleavedVertices;
        int interleavedStride;
};

#endif