public class GamePlane : MonoBehavior{
	private Mesh m_Mesh;
	private MeshFilter m_MeshFilter;
	public MeshRenderer m_Renderer;
	private Material	m_Material;
	public float	fTime = 0.0f;
	void Awake()
	{
		m_Material = Resource.Load("Plane") as Material;
		m_MeshFilter = gameObject.AddComponent<MeshFilter>();
		m_Renderer = gameObject.AddComponent<MeshRenderer>();
		
		m_Mesh = new Mesh();
		m_Mesh.name = "PlaneObject";
		
		//생성과 동시에 초기화..
		m_Mesh.vertices = new Vector3[]
		{
			new Vector3(-1.0f, 1.0f, 0.0f);
			new Vector3( 1.0f, 1.0f, 0.0f);
			new Vector3(-1.0f, -1.0f, 0.0f);
			new Vector3( 1.0f, -1.0f, 0.0f);	
		}
		/*
		//생성과 동시에 초기화를 하지 않으면 문제가 생긴다. 
		//Mesh의 vertices는 property로 되어 있기 때문에..
		//아래코드는 문제 코드..
		m_Mesh.vertices = new Vector3[4]
		m_Mesh.vertices[0] = new Vector3(-1.0f, 1.0f, 0.0f);
		m_Mesh.vertices[1] = new Vector3( 1.0f, 1.0f, 0.0f);
		m_Mesh.vertices[2] = new Vector3(-1.0f, -1.0f, 0.0f);
		m_Mesh.vertices[3] = new Vector3( 1.0f, -1.0f, 0.0f);
		*/
		m_Mesh.triangles = new int[] { 0,1,2,2,1,3}
		
		m_Mesh.uv = new Vector2[]
		{
			new Vector2(0.0f, 1.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
		};
		m_Renderer.sharedMaterial = m_Material;
		m_Mesh.RecalculateBounds();
		m_Mesh.RecalculateNormals();
		
		m_MeshFilter.sharedMesh = m_Mesh;
	}
	// Use this for initialization
	void Start () {
    }

    // Update is called once per frame
    void Update () {
		//fTime += Time.deltaTime;
		//transform.Translate( new Vector3(Mathf.Cos(fTime),Mathf.Sin(fTime),0.0f);
    }
}