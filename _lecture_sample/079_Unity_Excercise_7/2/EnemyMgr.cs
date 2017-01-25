using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMgr : MonoBehaviour {
	
	public CharacterController m_Ctl;
	public WayPoint m_Way;
	
	void Awake()
	{

	}
	
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 vDir = m_Way.GetDirection(transform);
		m_Ctl.Move(vDir);
	}
	
	void LateUpdate()
	{

	}
}
