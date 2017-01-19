public class Ingame : MonoBehavior{
	
	public GameObject m_Obj1 = null;
	public GameObject m_Obj2 = null;
	
	// Use this for initialization
	void Start () {
		object Obj = null;
		Obj = Resources.Load("Prefab/terrain");
		
		//인스턴스를 복사해서 반환하는 매서드
		m_Obj1  = (GameObject)(GameObject.Instantiate(Obj, new Vector3(-50,0,-50),Quaternion.Identity)); 
		
		//m_Obj1.SetActive(false);
		Destroy(m_Obj1, 10.0f);
		
		m_Obj2  = (GameObject)(GameObject.Instantiate(Obj, new Vector3(-50,0,100),Quaternion.Identity)); 
		Destroy(m_Obj2, 5.0f);
    }

    // Update is called once per frame
    void Update () {

    }
}