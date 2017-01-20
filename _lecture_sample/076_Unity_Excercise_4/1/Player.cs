public class Player : MonoBehavior{
	
	// 제외 오브젝트 선택
	public LayerMask m_LayerMask;
	public float m_fHeight;
	public bool  m_bJump = false;
	
    // Use this for initialization
    void Start () {
    }
	
	public void OnCollisionEnter(Collision col){
		m_bJump = false;
	}
	
	public void OnDrawGizmos()
	{
		Mesh mesh = GetComponent<MeshFilter>().sharedMesh;
		m_fHeight = mesh.bounds.size.y * transform.localScale.y;//바운딩 박스의 높이.
		Gizmos.color = Color.red;
		Gizmos.DrawRay(transform.position,
				transform.TransformDirection(-Vector3.up) * m_fHeight * 0.5f);
				
				
		Vector3 vBounds = GetComponent<Collider>().bounds.size;
		Vector3 vRight = new Vector3(transform.position.x + vBounds.x * 0.5f,  transform.position.y, transform.position.z);
		Vector3 vLeft = new Vector3(transform.position.x - vBounds.x * 0.5f,  transform.position.y, transform.position.z);
		
		Gizmos.DrawRay(vRight,
				transform.TransformDirection(-Vector3.up) * m_fHeight * 0.5f);
				
		Gizmos.DrawRay(vLeft,
				transform.TransformDirection(-Vector3.up) * m_fHeight * 0.5f);
	}
	
    // Update is called once per frame
    void Update () {
		Vector3 vDir = transform.TransformDirection(-Vector3.up);//-Vector3.up에 오브젝트의 월드매트릭스를 곱한다.
		Raycast vHit;
		Vector3 vBounds = GetComponent<Collider>().bounds.size;
		
		Vector3 vRight = new Vector3(transform.position.x + vBounds.x * 0.5f,  transform.position.y, transform.position.z);
		Vector3 vLeft = new Vector3(transform.position.x - vBounds.x * 0.5f,  transform.position.y, transform.position.z);
		
		
		if (GetComponent<Rigidbody>().velocity.y >= -2.0 && GetComponent<Rigidbody>().velocity.y <= 2.0)
		{
			//점프 최고점
		}
		else if(GetComponent<RigidBody>().velocity.y > 0.0f)
		{ 
			//점프 시작. 
		}
		else 
		{
			// 하강
		}
		
		
		//m_LayerMask.value = 8 | 9 | 11; //Unity에서 Layer Mask에서 설정으로 안하고 수작업으로 넣어줄때. 
		
		if(Physics.Raycast(
			transform.position,
			vDir,
			out vHit,
			2.5f,
			m_LayerMask.value))
		{
			m_bJump = false;
			Debug.Log("Physics.Raycast");	
		}
    }
}