using UnityEngine;
using System.Collections;

[RequireComponent(typeof(CharacterController))]
public class CharacterControl : MonoBehaviour
{

    private AnimationClip m_IdleClip;
    private AnimationClip m_WalkClip;
    private AnimationClip m_RunClip;
    private AnimationClip m_JumpClip;
    private AnimationClip m_FallClip;
    private Animation m_Animation;

    private float m_fJumpAnimaionSpeed = 4f;
    private float m_fFallAnimaionSpeed = 0.1f;
    private float m_fRunAnimaionSpeed = 1.5f;
    private float m_fWalkAnimaionSpeed = 1.5f;
    private float m_fIdleAnimaionSpeed = 0.5f;
    private float m_fSpeed = 2f;
    private float m_fRunSpeed = 5f;
    private float m_fJumpSpeed = 8f;
    private float m_fGravity = 20.0f;
    private CharacterController m_Controller;

    private float f_verticalSpeed = 0.0f;
    private float f_moveSpeed = 0.0f;
    private Vector3 v3_moveDirection = Vector3.zero;
    private bool b_isRun;
    private bool b_isBackward;
    private bool b_isJumping;

    private Quaternion m_qCurrentRotation;
    private Quaternion m_qRot;
    private float m_fRotateSpeed = 1.0f;

    private Vector3 m_vForward;
    private Vector3 m_vRight;
    private CollisionFlags m_CollisionFlags;
    private float m_fAirTime = 0.0f;
    private float m_fAirStartTime = 0.0f;
    private float m_fMinAirTime = 0.15f;

    private float m_fLockCameraTimer = 0.0f;
    private bool m_bMovingBack = false;
    private bool m_bMoving = false;
    private bool m_bWasMoving = false;


    void Awake()
    {
        m_Controller = GetComponent<CharacterController>();
        b_isRun = false;
        b_isBackward = false;
        b_isJumping = false;
        f_moveSpeed = m_fSpeed;
        m_CollisionFlags = CollisionFlags.CollidedBelow;
        m_Animation = GetComponent<Animation>();

        m_IdleClip = m_Animation.GetClip("Idle");
        m_WalkClip = m_Animation.GetClip("Walk");
        m_RunClip = m_Animation.GetClip("Run");
        m_JumpClip = m_Animation.GetClip("Jump");
        m_FallClip = m_Animation.GetClip("Fall");

        m_Animation[m_JumpClip.name].wrapMode = WrapMode.ClampForever;
        m_Animation[m_FallClip.name].wrapMode = WrapMode.ClampForever;
        m_Animation[m_IdleClip.name].wrapMode = WrapMode.Loop;
        m_Animation[m_RunClip.name].wrapMode = WrapMode.Loop;
        m_Animation[m_WalkClip.name].wrapMode = WrapMode.Loop;
    }

    void Start()
    {
        m_fAirStartTime = Time.time;
    }
	
	void GetPosition()
	{
		Ray ray = Camera.main.ScreenPointToRay(pos);
		Raycast hit;
		
		if(Physics.Raycast(ray, out hit, 100.0f))
		{
			if(hit.transform.tag == "Item")
			{
				GameObject obj = TPrefabMgr.Instance("CharEffect4", "CharEffect4", hit.point.x,hit.point.y,hit.point.z);
				
				Destroy(hit.transform.gameObject, 1.0f);
			}
			//GameObject obj2 = TPrefabMgr.Instance("CharEffect4", "CharEffect4", hit.point.x,hit.point.y,hit.point.z);
		}
	}
	
    void Update()
    {
		if(input.GetMouseButtonDown(0))
		{
			GetPosition(input.mousePosition);
		}
		
		
        Transform m_CameraTransform = Camera.main.transform;
        m_vForward = m_CameraTransform.TransformDirection(Vector3.forward);
        m_vForward.y = 0;
        m_vRight = new Vector3(m_vForward.z, 0, -m_vForward.x);

        float f_hor = Input.GetAxis("Horizontal");
        float f_ver = Input.GetAxis("Vertical");
        if (f_ver < 0)
        {
            b_isBackward = true;
        }
        else
        {
            b_isBackward = false;
        }

        Vector3 v3_targetDirection = (f_hor * m_vRight) + (f_ver * m_vForward);


        if (v3_targetDirection != Vector3.zero)
        {
            v3_moveDirection = Vector3.Slerp(v3_moveDirection, v3_targetDirection, m_fRotateSpeed * Time.deltaTime);
            v3_moveDirection = v3_moveDirection.normalized;
        }
        else
        {
            v3_moveDirection = Vector3.zero;
        }

        if (!b_isJumping)
        {
            if (Input.GetKey(KeyCode.LeftShift) || Input.GetKey(KeyCode.RightShift))
            {
                b_isRun = true;
                f_moveSpeed = m_fRunSpeed;
            }
            else
            {
                b_isRun = false;
                f_moveSpeed = m_fSpeed;
            }

            if (Input.GetButton("Jump"))
            {
                f_verticalSpeed = m_fJumpSpeed;
                b_isJumping = true;
            }
        }

        var v = Input.GetAxisRaw("Vertical");
        var h = Input.GetAxisRaw("Horizontal");

        // Are we moving backwards or looking backwards
        if (v < -0.2)
            m_bMovingBack = true;
        else
            m_bMovingBack = false;

        var m_bWasMoving = m_bMoving;
        m_bMoving = Mathf.Abs(h) > 0.1 || Mathf.Abs(v) > 0.1;


        if (IsGrounded())
        {
            m_fLockCameraTimer += Time.deltaTime;
            if (m_bMoving != m_bWasMoving)
                m_fLockCameraTimer = 0.0f;

            f_verticalSpeed = 0.0f;
            b_isJumping = false;
            m_fAirTime = 0.0f;
            m_fAirStartTime = Time.time;
        }
        else
        {
            f_verticalSpeed -= m_fGravity * Time.deltaTime;
            m_fAirTime = Time.time - m_fAirStartTime;
        }

        Vector3 v3_movement = (v3_moveDirection * f_moveSpeed) +
                               new Vector3(0, f_verticalSpeed, 0);
        v3_movement *= Time.deltaTime;
        m_CollisionFlags = m_Controller.Move(v3_movement);

        if (b_isJumping)
        {
            if (m_Controller.velocity.y > 0)
            {
                m_Animation[m_JumpClip.name].speed = m_fJumpAnimaionSpeed;
                m_Animation.CrossFade(m_JumpClip.name, 0.1f);
            }
            else
            {
                m_Animation[m_FallClip.name].speed = m_fFallAnimaionSpeed;
                m_Animation.CrossFade(m_FallClip.name, 0.1f);
            }
        }
        else
        {
            if (IsAir())
            {
                m_Animation[m_FallClip.name].speed = m_fFallAnimaionSpeed;
                m_Animation.CrossFade(m_FallClip.name, 0.1f);
            }
            else
            {
                if (m_Controller.velocity.sqrMagnitude < 0.1f)
                {
                    m_Animation[m_IdleClip.name].speed = m_fIdleAnimaionSpeed;
                    m_Animation.CrossFade(m_IdleClip.name, 0.1f);
                }
                else
                {
                    if (b_isRun)
                    {
                        m_Animation[m_RunClip.name].speed = m_fRunAnimaionSpeed;
                        m_Animation.CrossFade(m_RunClip.name, 0.1f);
                    }
                    else
                    {
                        m_Animation[m_WalkClip.name].speed = m_fWalkAnimaionSpeed;
                        m_Animation.CrossFade(m_WalkClip.name, 0.1f);
                    }
                }
            }
        }
        if (v3_moveDirection != Vector3.zero)
        {
            transform.rotation = Quaternion.LookRotation(v3_moveDirection);
        }

    }
    public bool IsGrounded()
    {
        if ((m_CollisionFlags & CollisionFlags.CollidedBelow) != 0)
        {
            return true;
        }
        return false;
    }
    public bool IsJumping()
    {
        return b_isJumping;
    }
    public bool IsAir()
    {
        return (m_fAirTime > m_fMinAirTime);
    }
    public bool IsMoveBackward()
    {
        return b_isBackward;
    }

    public float GetLockCameraTimer()
    {
        return m_fLockCameraTimer;
    }

    public bool IsMoving()
    {
        return Mathf.Abs(Input.GetAxisRaw("Vertical")) + Mathf.Abs(Input.GetAxisRaw("Horizontal")) > 0.5;
    }
}
