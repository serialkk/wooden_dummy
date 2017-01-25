using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WayPoint : MonoBehaviour {

	public Transform[] waypoints;
	public int m_iCurrentWay = 0;
	public int m_iTargetWay = 0;
	
	void Awake()
	{
		waypoints = gameObject.GetComponentsInChildren<Transform>();
		
		m_iTargetWay = (int)Mathf.Floor(Random.value * waypoints.Length); // Random: -1~+1 사이의 값이 리턴이 됨.
	}
	
	// 다음 웨이포인트로 가기위한 이동 방향.
	public Vector3 GetDirection(Transform ai)
	{
		Vector3 vDir = Vector3.zero;
		if(AwayFromWaypoint(ai, 5.0f))
		{
			m_iTargetWay = (int)Mathf.Floor(Random.value * waypoints.Length); // Random: -1~+1 사이의 값이 리턴이 됨.
		}
		vDir = (waypoints[m_iTargetWay].position - ai.position).normalized;
		
		return vDir;
	}
	
	public Vector3 GetDirectionToPlayer(Transform ai, Transform Target)
	{
		float fHeight = waypoints[m_iCurrentWay].position.y;
		Vector3 vCurrentPos = new Vector3(ai.position.x, fHeight, ai.position.z);
		Vector3 vPlayerPos = new Vector3(Target.position.x, Target.position.y, Target.position.z);
		Vector3 vDir = (vPlayerPos - vCurrentPos).normalized;
		return vDir;
	}
	
	public bool AwayFromWaypoint(Transform ai, float fDistance)
	{
		if(Vector3.Distance(ai.position, waypoints[m_iTargetWay].position >= fDistance)
		{
			return false;
		}
		return true;
	}
	
	public void OnDrawGizmos()
	{
		for( int i = 0; i < waypoints.Length; i++)
		{
			for( int j = 0; j < waypoints.Length; j++)
			{
				Gizmos.color = Color.red;
				Gizmos.DrawLine(waypoints[i].position, waypoints[j].position);
			}
			Gizmos.color = Color.green;
			Gizmos.DrawWireSphere(waypoints[i].position, 5.0f);
		}
	}
	
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

	}
	
	void LateUpdate()
	{

	}
}
