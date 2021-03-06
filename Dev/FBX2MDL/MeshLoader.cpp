#include "MeshLoader.h"


MeshLoader::MeshLoader()
{

}

std::vector<Vertex> MeshLoader::GetVertices()
{
	return _vertices;
}

void MeshLoader::_loadPositions(FbxMesh* fbxMesh)
{

	int controlNum = fbxMesh->GetControlPointsCount();

	FbxVector4* src = fbxMesh->GetControlPoints();

	for(int i=0;i<controlNum;++i)
	{
		Vertex vertex;
		ace::Vector3DF controlAry;
		controlAry.X=src[i][0];
		controlAry.Y=src[i][1];
		controlAry.Z=src[i][2];
		vertex.position=controlAry;
		vertex.normal=ace::Vector3DF(0,0,0);
		vertex.binormal=ace::Vector3DF(0,0,0);
		vertex.uv=ace::Vector2DF(0,0);
		vertex.subuv=ace::Vector2DF(0,0);
		for(int j=0;j<4;++j)
		{
			vertex.color[j]=0;
			vertex.weight[j]=0;
			vertex.weightIndexDivided[j]=0;
			vertex.weightIndexOriginal[j]=0;

		}

		_baseVertices.push_back(vertex);
	}
}

ace::Vector3DF MeshLoader::_loadNormal(FbxMesh* fbxMesh,int lControlPointIndex,int vertexId)
{
	ace::Vector3DF normal;
	for(int l = 0; l < fbxMesh->GetElementNormalCount(); ++l)
	{
		FbxGeometryElementNormal* leNormal = fbxMesh->GetElementNormal( l);

		if(leNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			switch (leNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				normal.X = leNormal->GetDirectArray().GetAt(vertexId)[0];
				normal.Y = leNormal->GetDirectArray().GetAt(vertexId)[1];
				normal.Z = leNormal->GetDirectArray().GetAt(vertexId)[2];
				break;
			case FbxGeometryElement::eIndexToDirect:
				{
					int id = leNormal->GetIndexArray().GetAt(vertexId);
					normal.X = leNormal->GetDirectArray().GetAt(id)[0];
					normal.Y = leNormal->GetDirectArray().GetAt(id)[1];
					normal.Z = leNormal->GetDirectArray().GetAt(id)[2];
				}
				break;
			}
		}

	}

	return normal;
}


ace::Vector3DF MeshLoader::_loadBinormal(FbxMesh* fbxMesh,int lControlPointIndex,int vertexId)
{
	ace::Vector3DF binormal;
	for(int l = 0; l < fbxMesh->GetElementBinormalCount(); ++l)
	{

		FbxGeometryElementBinormal* leBinormal = fbxMesh->GetElementBinormal( l);
		if(leBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			switch (leBinormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				binormal.X = leBinormal->GetDirectArray().GetAt(vertexId)[0];
				binormal.Y = leBinormal->GetDirectArray().GetAt(vertexId)[1];
				binormal.Z = leBinormal->GetDirectArray().GetAt(vertexId)[2];
				break;
			case FbxGeometryElement::eIndexToDirect:
				{
					int id = leBinormal->GetIndexArray().GetAt(vertexId);
					binormal.X = leBinormal->GetDirectArray().GetAt(id)[0];
					binormal.Y = leBinormal->GetDirectArray().GetAt(id)[1];
					binormal.Z = leBinormal->GetDirectArray().GetAt(id)[2];
				}
				break;
			}
		}
	}
	return binormal;
}

ace::Vector2DF MeshLoader::_loadUV(FbxMesh* fbxMesh, int lControlPointIndex, int vertexId, int polygonCount, int polygonVert)
{
	ace::Vector2DF uv;
	for (int l = 0; l < fbxMesh->GetElementUVCount(); ++l)
	{
		FbxGeometryElementUV* leUV = fbxMesh->GetElementUV( l);

		switch (leUV->GetMappingMode())
		{
		default:
			break;
		case FbxGeometryElement::eByControlPoint:
			switch (leUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				uv.X=leUV->GetDirectArray().GetAt(lControlPointIndex)[0];
				uv.Y=leUV->GetDirectArray().GetAt(lControlPointIndex)[1];
				break;
			case FbxGeometryElement::eIndexToDirect:
				{
					int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
					uv.X=leUV->GetDirectArray().GetAt(id)[0];
					uv.Y=leUV->GetDirectArray().GetAt(id)[1];
				}
				break;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{									 
				int lTextureUVIndex = fbxMesh->GetTextureUVIndex(polygonCount, polygonVert);
				switch (leUV->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				case FbxGeometryElement::eIndexToDirect:
					{
						uv.X=leUV->GetDirectArray().GetAt(lTextureUVIndex)[0];
						uv.Y=leUV->GetDirectArray().GetAt(lTextureUVIndex)[1];
					}
					break;
				}
			}
			break;
		}
	}
	return uv;
}

uint8_t* MeshLoader::_loadColor(FbxMesh* fbxMesh,int lControlPointIndex,int vertexId)
{
	uint8_t color[4]={0,0,0,0};

	for (int l = 0; l < fbxMesh->GetElementVertexColorCount(); l++)
	{
		FbxGeometryElementVertexColor* leVtxc = fbxMesh->GetElementVertexColor( l);

		switch (leVtxc->GetMappingMode())
		{
		default:
			break;
		case FbxGeometryElement::eByControlPoint:
			switch (leVtxc->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				color[0]=(uint8_t)leVtxc->GetDirectArray().GetAt(lControlPointIndex)[0]*255;
				color[1]=(uint8_t)leVtxc->GetDirectArray().GetAt(lControlPointIndex)[1]*255;
				color[2]=(uint8_t)leVtxc->GetDirectArray().GetAt(lControlPointIndex)[2]*255;
				color[3]=(uint8_t)leVtxc->GetDirectArray().GetAt(lControlPointIndex)[3]*255;
				break;
			case FbxGeometryElement::eIndexToDirect:
				{
					int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
					color[0]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[0]*255;
					color[1]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[1]*255;
					color[2]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[2]*255;
					color[3]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[3]*255;
				}
				break;
			default:
				break; // other reference modes not shown here!
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch (leVtxc->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					color[0]=(uint8_t)leVtxc->GetDirectArray().GetAt(vertexId)[0]*255;
					color[1]=(uint8_t)leVtxc->GetDirectArray().GetAt(vertexId)[1]*255;
					color[2]=(uint8_t)leVtxc->GetDirectArray().GetAt(vertexId)[2]*255;
					color[3]=(uint8_t)leVtxc->GetDirectArray().GetAt(vertexId)[3]*255;
					break;
				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leVtxc->GetIndexArray().GetAt(vertexId);
						color[0]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[0]*255;
						color[1]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[1]*255;
						color[2]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[2]*255;
						color[3]=(uint8_t)leVtxc->GetDirectArray().GetAt(id)[3]*255;
					}
					break;
				}
			}
			break;
		}
	}
	return color;
}

void MeshLoader::_loadWeight(FbxMesh* fbxMesh)
{
	int skinCount=fbxMesh->GetDeformerCount(FbxDeformer::eSkin);

	for(int i=0;i<skinCount;++i)
	{
		FbxSkin* skin = (FbxSkin*)fbxMesh->GetDeformer(i,FbxDeformer::eSkin);

		int clusterNum = skin->GetClusterCount();

		for(int j=0;j<clusterNum;++j)
		{
			FbxCluster* cluster = skin->GetCluster(j);

			int pointNum = cluster->GetControlPointIndicesCount();
			int* pointAry = cluster->GetControlPointIndices();
			double* weightAry = cluster->GetControlPointWeights();

			for(int k=0;k<pointNum;++k)
			{
				int index = pointAry[i];
				float weight = (float)weightAry[i];

				_vertices[index].weight[j]=weight;
			}
		}
	}
}

void MeshLoader::_loadFaceIndices(FbxMesh* fbxMesh)
{
	int PolygonVertexNum=fbxMesh->GetPolygonVertexCount();
	int *IndexAry = fbxMesh->GetPolygonVertices();

	Face face;
	int faceIndexer=0;
	for(int i=0;i<PolygonVertexNum;++i)
	{
		face.vertexIndex[faceIndexer++]=IndexAry[i];
		if(faceIndexer==3)
		{
			faceIndexer=0;
			_faces.push_back(face);
		}
	}
}

void MeshLoader::Load(FbxMesh* fbxMesh)
{
	_loadPositions(fbxMesh);

	_loadVertices(fbxMesh);
	//_loadFaceIndices(fbxMesh);

	//_loadNormals(fbxMesh);
	//_loadBinormals(fbxMesh);
	//_loadUVs(fbxMesh);
	//_loadColors(fbxMesh);
	//_loadWeights();

	_loadTextures(fbxMesh);
}

void MeshLoader::WriteVertices(ace::BinaryWriter* writer)
{
	printf("Control Point Num = %d\n",_vertices.size());
	writer->Push((int32_t)_vertices.size());

	ace::Vector3DF zero3 = ace::Vector3DF(0,0,0);
	ace::Vector2DF zero2 = ace::Vector2DF(0,0);


	for(int i=0;i<_vertices.size();++i)
	{
		printf("CP(%f, %f, %f)\n",_vertices[i].position.X,_vertices[i].position.Y,_vertices[i].position.Z);
		writer->Push(_vertices[i].position);

		printf("NV(%f, %f, %f)\n",_vertices[i].normal.X,_vertices[i].normal.Y,_vertices[i].normal.Z);
		writer->Push(_vertices[i].normal);
		writer->Push(zero3);

		printf("UV(%f, %f)\n",_vertices[i].uv.X,_vertices[i].uv.Y);
		writer->Push(_vertices[i].uv);
		writer->Push(_vertices[i].subuv);

		//頂点カラー
		writer->Push((uint8_t)_vertices[i].color[0]);
		writer->Push((uint8_t)_vertices[i].color[1]);
		writer->Push((uint8_t)_vertices[i].color[2]);
		writer->Push((uint8_t)_vertices[i].color[3]);

		//頂点ウェイト
		writer->Push((uint8_t)255);
		writer->Push((uint8_t)0);
		writer->Push((uint8_t)0);
		writer->Push((uint8_t)0);

		for (int j = 0; j < 4; ++j)
		{
			//writer->Push(_vertices[i].weightIndexOriginal[j]);
			writer->Push((uint8_t)0);
		}

		for (int j = 0; j < 4; ++j)
		{
			//writer->Push(_vertices[i].weightIndexDivided[j]);
			writer->Push((uint8_t)0);
		}
	}
}

void MeshLoader::WriteFaces(ace::BinaryWriter* writer)
{

	printf("Face Num = %d\n",_faces.size());
	writer->Push((int32_t) _faces.size());
	for (auto ite = _faces.begin(); ite != _faces.end(); ++ite)
	{
		printf("FI(");
		for (int i = 0; i < 3; ++i)
		{
			printf("%d, ",ite->vertexIndex[i]);
			writer->Push((int32_t) ite->vertexIndex[i]);
		}
		printf(")\n");
	}
}

void MeshLoader::WriteMaterials(ace::BinaryWriter* writer)
{
	printf("Material Num = %d\n",_materials.size());
	writer->Push((int32_t)_materials.size());
	for(auto ite=_materials.begin();ite!=_materials.end();++ite)
	{
		writer->Push(ite->Type);
		for(int i=0;i<3;++i)
		{
			printf("%s\n",ite->texture[i].c_str());
			writer->Push(ace::ToAString(ite->texture[i].c_str()));
		}
	}

}

void MeshLoader::_loadFaceMaterials(FbxMesh* fbxMesh)
{

}


void MeshLoader::_loadBoneAttachments(FbxMesh* fbxMesh)
{

}

void MeshLoader::WriteFaceMaterials(ace::BinaryWriter* writer)
{
	writer->Push((int32_t)0);
}

void MeshLoader::WriteBoneAttachments(ace::BinaryWriter* writer)
{
	writer->Push((int32_t)0);
}

void MeshLoader::_loadTextures(FbxMesh* fbxMesh)
{
	FbxNode* node = fbxMesh->GetNode();

	int materialCount = node->GetMaterialCount();

	const char* mats[3]={FbxSurfaceMaterial::sDiffuse,FbxSurfaceMaterial::sNormalMap,FbxSurfaceMaterial::sSpecular};

	for (int i = 0; materialCount > i; i++) {

		FbxSurfaceMaterial* material = node->GetMaterial(i);
		Material mat;
		mat.Type=0;
		for(int j=0;j<3;++j)
		{
			FbxProperty prop = material->FindProperty(mats[j]);

			int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

			if(0 < layeredTextureCount) {

				for(int j = 0; layeredTextureCount > j; j++) {

					FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
					int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

					for(int k = 0; textureCount > k; k++) {
						FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

						if(texture) {
							//--- テクスチャ名を取得 ---//
							//std::string textureName = texture->GetName();
							std::string textureName = texture->GetRelativeFileName();

							//--- UVSet名を取得 ---//
							std::string UVSetName = texture->UVSet.Get().Buffer();

							mat.texture[j]=textureName;
						}
					}
				}
			}
			else {
				//--- テクスチャ数を取得 ---//
				int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

				if(0 < fileTextureCount) {
					for(int j = 0; fileTextureCount > j; j++) {
						FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
						if(texture) {
							//std::string textureName = texture->GetName();
							std::string textureName = texture->GetRelativeFileName();

							//--- UVSet名を取得 ---//
							std::string UVSetName = texture->UVSet.Get().Buffer();

							mat.texture[j]=textureName;
						}
					}
				}
			}
		}
		_materials.push_back(mat);
	}
}

void MeshLoader::_loadVertices(FbxMesh* fbxMesh)
{
	int lPolygonCount = fbxMesh->GetPolygonCount();
	FbxVector4* lControlPoints = fbxMesh->GetControlPoints();

	int vertexId = 0;
	for (int i = 0; i < lPolygonCount; i++)
	{
		int l;

		int lPolygonSize = fbxMesh->GetPolygonSize(i);

		int cIndices[3];

		for (int j = 0; j < lPolygonSize; j++)
		{
			int lControlPointIndex = fbxMesh->GetPolygonVertex(i, j);

			Vertex vertex;

			vertex=_baseVertices[lControlPointIndex];

			uint8_t* color = _loadColor(fbxMesh,lControlPointIndex,vertexId);

			vertex.color[0]=color[0];
			vertex.color[1]=color[1];
			vertex.color[2]=color[2];
			vertex.color[3]=color[3];

			vertex.uv = _loadUV(fbxMesh,lControlPointIndex,vertexId,i,j);

			vertex.normal = _loadNormal(fbxMesh,lControlPointIndex,vertexId);

			vertex.binormal = _loadBinormal(fbxMesh,lControlPointIndex,vertexId);

			int index = -1;
			for(int k=0;k<_vertices.size();++k)
			{
				if(_vertices[k]==vertex)
				{
					printf("SAME! %d\n",k);
					index=k;
					break;
				}
			}

			//not found same vertex
			if(index==-1)
			{
				_vertices.push_back(vertex);
				cIndices[j]=(int)_vertices.size()-1;
			}
			else
			{
				cIndices[j]=index;
			}

			vertexId++;
		} // for polygonSize

		Face face;
		face.vertexIndex[0]=cIndices[0];
		face.vertexIndex[1]=cIndices[1];
		face.vertexIndex[2]=cIndices[2];
		_faces.push_back(face);

	} // for polygonCount
}