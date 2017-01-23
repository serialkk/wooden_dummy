using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HeroineMgr : MonoBehaviour {

	public CharacterController m_Ctl;
	public Animation     m_Animation;
	
	//이 스크립트를 캐릭터 오브젝트에 추가하고 인스펙터에서 애니메이션을 드래그해서 연결 시킬 수 있다.
	public AnimationClip m_Idle;
	public AnimationClip m_Walk;
	public AnimationClip m_Run;
	public AnimationClip m_Jump;
	public AnimationClip m_Fall;
	
	void Awake()
	{
		m_Ctl = GetComponent<CharacterController>();
		m_Animation = GetComponent<Animation>();
		
		m_Animation[m_Idle.name].wrapMode = WrapMode.Loop;
		m_Animation[m_Jump.name].wrapMode = WrapMode.Once;
	}
    // Use this for initialization
    void Start()
    {
		//m_Animation.Play(); // 동작과 동작사이를 보간을 하진 않는다.
		m_Animation.CrossFade(m_Walk.name, 0.1f);//동작에서 다른 동작이 변경될때 애니메이션을 보간한다.
    }

    // Update is called once per frame
    void Update()
    {
		if(Input.GetButton("Jump"))
		{
			m_Animation.CrossFade(m_Jump.name, 0.1f);
			//m_Animation.CrossFadeQueued(m_Jump.name, 0.1f);//이전 애니메이션 동작이 끝나고 다음 애니메이션이 시작된다.
		}
		//else
		//{
		//	m_Animation.CrossFade(m_Idle.name, 0.1f);
		//}
    }
}
