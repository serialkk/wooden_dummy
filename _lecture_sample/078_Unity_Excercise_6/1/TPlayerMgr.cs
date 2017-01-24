using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPlayerMgr : MonoBehaviour {

	public CharacterController m_Ctl;
	Animation m_Animation;
	CollisionFlags m_CollisionFlags;
	
	AnimationClip m_Idle = null;
	AnimationClip m_Walk = null;
	AnimationClip m_Run = null;
	AnimationClip m_Jump = null;
	AnimationClip m_Fall = null;
	Vector3 m_vMoveDirection = Vector3.zero;
	float	m_fVerticalSpeed = 0.0f;
	float	m_fRunSpeed =1.0f;
	bool m_bJump = false;
	bool m_bRun = false;
	
	void Awake()
	{
		m_Ctl = GetComponent<CharacterController>();
		m_Animation = GetComponent<Animation>();
		
		//현재 애니메이션에 연결된 클립들을 가져옴.
		m_Idle = m_Animation.GetClip("Idle");
		m_Walk = m_Animation.GetClip("Walk");
		m_Run = m_Animation.GetClip("Run");
		m_Jump = m_Animation.GetClip("Jump");
		m_Fall = m_Animation.GetClip("Fall");
		
	}
	
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 vForward = Camera.main.transform.TransformDirection(Vector3.forward);
		vForward.y = 0;
		Vector3 vRight = new Vector3(vForward.z, 0, -vForward.x);
		
		float fHor = Input.GetAxis("Horizontal");
		float fVer = Input.GetAxis("Vertical");
		
		Vector3 vTargetDirection = (vForward * fVer) + (vRight * fHor);
		if(vTargetDirection != Vector3.zero)
		{
			vMoveDirection = Vector3.Lerp(m_vMoveDirection, vTargetDirection, Time.deltaTime);
			m_vMoveDirection = vMoveDirection.normalized;
			m_Animation.CrossFade(m_Walk.name, 0.1f);
		}else
		{
			m_vMoveDirection = Vector3.zero;
			m_Animation.CrossFade(m_Idle.name, 0.1f);
		}
		bool bGround = (CollisionFlags.CollidedBelow & m_CollisionFlags) != 0;
		if(bGround == true)
		{
			m_bRun = false;
			m_bJump = false;
			m_fRunSpeed = 1.0f;
			if ( Input.GetKey(KeyCode.LeftShift))
            {
				m_fRunSpeed = 3.0f;
                m_bRun = true;
            }
			//jump
			if(Input.GetButton("Jump"))
			{
				m_fVerticalSpeed  = 8.0f;
				m_bJump = true;
			}
		}
		else
		{
			m_fVerticalSpeed -= 20.0f * Time.deltaTime;
		}
		
		
		Vector3 vMovement = m_vMoveDirection*m_fRunSpeed + new Vector3(0,m_fVerticalSpeed,0);
		vMovement *=Time.deltaTime;
		
		m_CollisionFlags = m_Ctl.Move(vMovement);//m_vMoveDirection);
		
		if(m_bJump)
		{
			if(m_Ctl.velocity.y > 0.0f)
			{
				m_Animation.CrossFade(m_Jump.name, 0.1f);
			}
			else
			{
				m_Animation.CrossFade(m_Fall.name, 0.1f);
			}
		}
		else
		{
			if(m_bRun)
			{
				m_Animation.CrossFade(m_Run.name, 0.1f);
			}
		}
		
		
		
		if(m_vMoveDirection != Vector3.zero)
		{
			transform.rotation = Quaternion.LookRotation(m_vMoveDirection);
			
		}
	}
	
	void LateUpdate()
	{
		Camera.main.transform.LookAt(transform);
		Vector3 vForward = transform.TransformDirection(Vector3.forward);
		vForward = vForward.normalized;
		Vector3 vDir = transform.position + (-vForward * 5.0f);
		Camera.main.transform.position = new Vector3(
		vDir.x, Camera.main.transform.y,vDir.z);
		);
	}
}
