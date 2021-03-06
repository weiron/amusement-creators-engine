﻿
#pragma once

#include "ace.Model.h"
#include <Utility/ace.BinaryReader.h>

namespace ace
{
	class Model_Imp
		: public Model
		, public ReferenceObject
	{
	public:
		class MeshGroup
			: public ReferenceObject
		{
		public:
			std::vector<Mesh_Imp*>		Meshes;
			Deformer_Imp*				Deformer_;

			MeshGroup() = default;
			virtual ~MeshGroup();
		};

	private:
		std::vector<MeshGroup*>		m_meshGroups;
		std::vector<astring>		m_animationClipNames;
		std::vector<AnimationClip*>	m_animationClips;

		Graphics*					m_graphics;

		std::set<RenderedModelObject3D*>	m_observers;

		void Reset();

	public:
		Model_Imp(Graphics* graphics);
		virtual ~Model_Imp();

		bool Load(Graphics* g, std::vector<uint8_t>& data, const achar* path);

		/**
			@brief	モデルに変更が発生したことを伝える先を登録する。
			@param	model	観察者
		*/
		void Attach(RenderedModelObject3D* model);

		/**
			@brief	モデルに変更が発生したことを伝える先を解除する。
			@param	model	観察者
		*/
		void Detach(RenderedModelObject3D* model);

		void Reload(std::vector<uint8_t>& data, const achar* path);

	private:
		MeshGroup* LoadMeshGroup(Graphics* g, BinaryReader& reader, const achar* path);
		Mesh_Imp* LoadMesh(Graphics* g, BinaryReader& reader, const achar* path);
		Deformer_Imp* LoadDeformer(Graphics* g, BinaryReader& reader, const achar* path);

		void LoadAnimationClip(BinaryReader& reader, std::vector<AnimationSource*>& source);
		AnimationSource* LoadAnimationSource(BinaryReader& reader);
		KeyframeAnimation* LoadKeyframeAnimation(BinaryReader& reader);

	public:
		std::vector<AnimationClip*>& GetAnimationClips() { return m_animationClips; }
		std::vector<astring>& GetAnimationClipNames() { return m_animationClipNames; }
		std::vector < MeshGroup*> GetMeshGroups() { return m_meshGroups; }
		
		// IReferenceを継承したデバイスオブジェクト向け定義
#if !SWIG
	public:
		virtual int GetRef() { return ReferenceObject::GetRef(); }
		virtual int AddRef() { return ReferenceObject::AddRef(); }
		virtual int Release() { return ReferenceObject::Release(); }
#endif
	};
}