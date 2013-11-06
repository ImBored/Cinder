/*
 Copyright (c) 2010, The Barbarian Group
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <vector>
#include "cinder/Vector.h"
#include "cinder/AxisAlignedBox.h"
#include "cinder/DataSource.h"
#include "cinder/DataTarget.h"
#include "cinder/Matrix.h"
#include "cinder/Color.h"
#include "cinder/Rect.h"

namespace cinder {
	
	/*! \brief The TriMesh allows you to create a series of vertices linked into a mesh.
	 
	 \example
	 
	 
	 To create a simple pair of Triangles linked into a quad first add the 4 vertices to the TriMesh using \a appendVertex() and then
	 add the vertices using the \a appendTriangle() method and passing the indices of the 3 vertices you want to connect
	 
	 Trimesh mesh;
	 mesh.appendVertex(Vec3f(10, 10, 0 )); // appends the vertex
	 mesh.appendColorRGB( Color(1, 0, 0) ); // sets the color for the vertex to red
	 mesh.appendVertex( Vec3f(10, 100, 0) ); // appends the next vertex
	 mesh.appendColorRGB( Color( 0, 1, 0 ) ); // sets the color for the next vertex to green
	 mesh.appendVertex( Vec3f(100, 100, 0) );
	 mesh.appendColorRGB( Color(  0, 1, 0 ) );
	 mesh.appendVertex( Vec3f(100, 10, 0 ));
	 mesh.appendColorRGB( Color( 1, 0, 0 ) );
	 
	 // get the index of the vertex. not necessary with this example, but good practice
	 int vIdx0 = mesh.getNumVertices() - 4;
	 int vIdx1 = mesh.getNumVertices() - 3;
	 int vIdx2 = mesh.getNumVertices() - 2;
	 int vIdx3 = mesh.getNumVertices() - 1;
	 
	 // now create the triangles from the vertices
	 mesh.appendTriangle( vIdx0, vIdx1, vIdx2 );
	 mesh.appendTriangle( vIdx0, vIdx2, vIdx3 );
	 
	*/
	 
class TriMesh {
 public:
	
	void		clear();
	
	bool		hasNormals() const { return ! mNormals.empty(); }
	bool		hasTangents() const { return ! mTangents.empty(); }
	bool		hasColorsRGB() const { return ! mColorsRGB.empty(); }
	bool		hasColorsRGBA() const { return ! mColorsRGBA.empty(); }
	bool		hasTexCoords() const { return ! mTexCoords.empty(); }

	/*! Creates a vertex which can be referred to with appendTriangle() or appendIndices() */
	void		appendVertex( const Vec3f &v ) { mVertices.push_back( v ); }
	/*! Appends multiple vertices to the TriMesh which can be referred to with appendTriangle() or appendIndices() */
	void		appendVertices( const Vec3f *verts, size_t num );
	/*! Appends multiple vertices to the TriMesh which can be referred to with appendTriangle() or appendIndices() */
	void		appendVertices( const Vec4d *verts, size_t num );
	/*! Appends a normal  */
	void		appendNormal( const Vec3f &v ) { mNormals.push_back( v ); }
	/*! appendNormals functions similarly to the appendVertices method, appending multiple normals to be associated with the triangle faces. Normals and triangles are associated by index, so if you have created 3 vertices and one Triangle, you would append a single normal for the face of the triangles */
	void		appendNormals( const Vec3f *normals, size_t num );
	/*! appendNormals functions similarly to the appendVertices method, appending multiple normals to be associated with the triangle faces. Normals and triangles are associated by index, so if you have created 3 vertices and one Triangle, you would append a single normal for the face of the triangles */
	void		appendNormals( const Vec4d *normals, size_t num );
	/*! Appends a tangent  */
	void		appendTangent( const Vec3f &v ) { mTangents.push_back( v ); }
	/*! appendTangents functions similarly to the appendVertices method, appending multiple tangents to be associated with the triangle faces. Tangents and triangles are associated by index, so if you have created 3 vertices and one Triangle, you would append a single tangent for the face of the triangles */
	void		appendTangents( const Vec3f *tangents, size_t num );
	/*! appendTangents functions similarly to the appendVertices method, appending multiple tangents to be associated with the triangle faces. Tangents and triangles are associated by index, so if you have created 3 vertices and one Triangle, you would append a single tangent for the face of the triangles */
	void		appendTangents( const Vec4d *tangents, size_t num );
	/*! this sets the color used by a triangle generated by the TriMesh */ 
	void		appendColorRgb( const Color &rgb ) { mColorsRGB.push_back( rgb ); }
	/*! this sets the color used by a triangle generated by the TriMesh */
	void		appendColorRgba( const ColorA &rgba ) { mColorsRGBA.push_back( rgba ); }
	/*! appends a texture coordinate in [-1,1] space to be applied to generated triangles. The coordinates are associated with the vertexes of the TriMesh, not the generated triangles when they are drawn */
	void		appendTexCoord( const Vec2f &v ) { mTexCoords.push_back( v ); }
	
	/*! Appends multiple RGB colors to the TriMesh */ 
	void		appendColorsRgb( const Color *rgbs, size_t num );
	/*! Appends multiple RGBA colors to the TriMesh */
	void		appendColorsRgba( const ColorA *rgbas, size_t num );
	/*! Appends multiple texcoords to the TriMesh */
	void		appendTexCoords( const Vec2f *texcoords, size_t num );
	
	/*! after creating three vertices, pass the indices of the three vertices to create a triangle from them. Until this is done, unlike in an OpenGL triangle strip, the 
	 triangle will not actually be generated and stored by the TriMesh
	*/
	void		appendTriangle( uint32_t v0, uint32_t v1, uint32_t v2 )
	{ mIndices.push_back( v0 ); mIndices.push_back( v1 ); mIndices.push_back( v2 ); }
	//! Appends \a num vertices to the TriMesh pointed to by \a indices
	void		appendIndices( const uint32_t *indices, size_t num );

	//! Returns the total number of indices contained by a TriMesh. This should be number of triangles/3
	size_t		getNumIndices() const { return mIndices.size(); }
	//! Returns the total number of triangles contained by a TriMesh. This should be number of indices*3
	size_t		getNumTriangles() const { return mIndices.size() / 3; }
	//! Returns the total number of indices contained by a TriMesh. This should be number of triangles/3
	size_t		getNumVertices() const { return mVertices.size(); }

	//! Puts the 3 vertices of triangle number \a idx into \a a, \a b and \a c.
	void		getTriangleVertices( size_t idx, Vec3f *a, Vec3f *b, Vec3f *c ) const;

	//! Returns all the vertices for a mesh in a std::vector as Vec3f objects 
	std::vector<Vec3f>&				getVertices() { return mVertices; }
	//! Returns all the vertices for a mesh in a std::vector as Vec3f objects 
	const std::vector<Vec3f>&		getVertices() const { return mVertices; }
	//! Returns all the normals for a mesh in a std::vector as Vec3f objects. There will be one of these for each triangle face in the mesh
	std::vector<Vec3f>&				getNormals() { return mNormals; }
	//! Returns all the normals for a mesh in a std::vector as Vec3f objects. There will be one of these for each triangle face in the mesh
	const std::vector<Vec3f>&		getNormals() const { return mNormals; }
	//! Returns all the tangents for a mesh in a std::vector as Vec3f objects. There will be one of these for each triangle face in the mesh
	std::vector<Vec3f>&				getTangents() { return mTangents; }
	//! Returns all the tangents for a mesh in a std::vector as Vec3f objects. There will be one of these for each triangle face in the mesh
	const std::vector<Vec3f>&		getTangents() const { return mTangents; }
	//! Returns a std::vector of RGB colors of the triangles faces. There will be one of these for each triangle face in the mesh
	std::vector<Color>&				getColorsRGB() { return mColorsRGB; }
	//! Returns a std::vector of RGB colors of the triangles faces. There will be one of these for each triangle face in the mesh
	const std::vector<Color>&		getColorsRGB() const { return mColorsRGB; }
	//! Returns a std::vector of RGBA colors of the triangles faces. There will be one of these for each triangle face in the mesh
	std::vector<ColorA>&			getColorsRGBA() { return mColorsRGBA; }
	//! Returns a std::vector of RGBA colors of the triangles faces. There will be one of these for each triangle face in the mesh
	const std::vector<ColorA>&		getColorsRGBA() const { return mColorsRGBA; }
	//! Returns a std::vector of Texture coordinates as Vec2fs. There will be one texture coord for each vertex in the TriMesh
	std::vector<Vec2f>&				getTexCoords() { return mTexCoords; }	
	//! Returns a std::vector of Texture coordinates as Vec2fs. There will be one texture coord for each vertex in the TriMesh
	const std::vector<Vec2f>&		getTexCoords() const { return mTexCoords; }	
	//! Trimesh indices are ordered such that the indices of triangle T are { indices[T*3+0], indices[T*3+1], indices[T*3+2] }
	std::vector<uint32_t>&			getIndices() { return mIndices; }		
	//! Trimesh indices are ordered such that the indices of triangle T are { indices[T*3+0], indices[T*3+1], indices[T*3+2] }
	const std::vector<uint32_t>&	getIndices() const { return mIndices; }		

	//! Calculates the bounding box of all vertices
	AxisAlignedBox3f	calcBoundingBox() const;
	//! Calculates the bounding box of all vertices as transformed by \a transform
	AxisAlignedBox3f	calcBoundingBox( const Matrix44f &transform ) const;

	//! This reads a TriMesh in from a data file that was serialized using the write() function.
	void		read( DataSourceRef in );
	//! This writes a TriMesh to a proprietary file format to be read using the read() function.
	void		write( DataTargetRef out ) const;

	//! Adds or replaces normals by calculating them from the vertices and faces.
	void		recalculateNormals();
	//! Adds or replaces tangents by calculating them from the normals.
	void		recalculateTangents();
	
 private:
	std::vector<Vec3f>		mVertices;
	std::vector<Vec3f>		mNormals;
	std::vector<Vec3f>		mTangents;
	std::vector<Color>		mColorsRGB;
	std::vector<ColorA>		mColorsRGBA;
	std::vector<Vec2f>		mTexCoords;
	std::vector<uint32_t>	mIndices;
};

class TriMesh2d {
 public:
	void		clear();
	
	bool		hasColorsRgb() const { return ! mColorsRgb.empty(); }
	bool		hasColorsRgba() const { return ! mColorsRgba.empty(); }
	bool		hasTexCoords() const { return ! mTexCoords.empty(); }

	/*! Creates a vertex which can be referred to with appendTriangle() or appendIndices() */
	void		appendVertex( const Vec2f &v ) { mVertices.push_back( v ); }
	/*! Appends multiple vertices which can be referred to with appendTriangle() or appendIndices() */
	void		appendVertices( const Vec2f *verts, size_t num );
	/*! this sets the color used by a triangle generated by the TriMesh */ 
	void		appendColorRgb( const Color &rgb ) { mColorsRgb.push_back( rgb ); }
	/*! this sets the color used by a triangle generated by the TriMesh */
	void		appendColorRgba( const ColorA &rgba ) { mColorsRgba.push_back( rgba ); }
	/*! appends a texture coordinate in [-1,1] space to be applied to generated triangles. The coordinates are associated with the vertexes of the TriMesh, not the generated triangles when they are drawn */
	void		appendTexCoord( const Vec2f &v ) { mTexCoords.push_back( v ); }
	
	/*! Appends multiple RGB colors to the TriMesh */ 
	void		appendColorsRgb( const Color *rgbs, size_t num );
	/*! Appends multiple RGBA colors to the TriMesh */
	void		appendColorsRgba( const ColorA *rgbas, size_t num );
	/*! Appends multiple texcoords to the TriMesh */
	void		appendTexCoords( const Vec2f *texcoords, size_t num );
	
	/*! after creating three vertices, pass the indices of the three vertices to create a triangle from them. Until this is done, unlike in an OpenGL triangle strip, the 
	 triangle will not actually be generated and stored by the TriMesh
	*/
	void		appendTriangle( uint32_t v0, uint32_t v1, uint32_t v2 )
	{ mIndices.push_back( v0 ); mIndices.push_back( v1 ); mIndices.push_back( v2 ); }
	//! Appends \a num vertices to the TriMesh2d pointed to by \a indices
	void		appendIndices( const uint32_t *indices, size_t num );
	
	//! Returns the total number of indices contained by a TriMesh. This should be number of triangles/3
	size_t		getNumIndices() const { return mIndices.size(); }
	//! Returns the total number of triangles contained by a TriMesh. This should be number of indices*3
	size_t		getNumTriangles() const { return mIndices.size() / 3; }
	//! Returns the total number of indices contained by a TriMesh. This should be number of triangles/3
	size_t		getNumVertices() const { return mVertices.size(); }

	//! Puts the 3 vertices of triangle number \a idx into \a a, \a b and \a c.
	void		getTriangleVertices( size_t idx, Vec2f *a, Vec2f *b, Vec2f *c ) const;

	//! Returns all the vertices for a mesh in a std::vector as Vec2f objects 
	std::vector<Vec2f>&				getVertices() { return mVertices; }
	//! Returns all the vertices for a mesh in a std::vector as Vec2f objects 
	const std::vector<Vec2f>&		getVertices() const { return mVertices; }
	//! Returns a std::vector of RGB colors of the triangles faces. There will be one of these for each triangle face in the mesh
	std::vector<Color>&				getColorsRGB() { return mColorsRgb; }
	//! Returns a std::vector of RGB colors of the triangles faces. There will be one of these for each triangle face in the mesh
	const std::vector<Color>&		getColorsRGB() const { return mColorsRgb; }
	//! Returns a std::vector of RGBA colors of the triangles faces. There will be one of these for each triangle face in the mesh
	std::vector<ColorA>&			getColorsRGBA() { return mColorsRgba; }
	//! Returns a std::vector of RGBA colors of the triangles faces. There will be one of these for each triangle face in the mesh
	const std::vector<ColorA>&		getColorsRGBA() const { return mColorsRgba; }
	//! Returns a std::vector of Texture coordinates as Vec2fs. There will be one texture coord for each vertex in the TriMesh
	std::vector<Vec2f>&				getTexCoords() { return mTexCoords; }	
	//! Returns a std::vector of Texture coordinates as Vec2fs. There will be one texture coord for each vertex in the TriMesh
	const std::vector<Vec2f>&		getTexCoords() const { return mTexCoords; }	
	//! Trimesh indices are ordered such that the indices of triangle T are { indices[T*3+0], indices[T*3+1], indices[T*3+2] }
	std::vector<uint32_t>&			getIndices() { return mIndices; }
	//! Trimesh indices are ordered such that the indices of triangle T are { indices[T*3+0], indices[T*3+1], indices[T*3+2] }
	const std::vector<uint32_t>&	getIndices() const { return mIndices; }

	//! Calculates the bounding box of all vertices
	Rectf	calcBoundingBox() const;

 private:
	std::vector<Vec2f>		mVertices;
	std::vector<Color>		mColorsRgb;
	std::vector<ColorA>		mColorsRgba;
	std::vector<Vec2f>		mTexCoords;
	std::vector<uint32_t>	mIndices;
};

} // namespace cinder
