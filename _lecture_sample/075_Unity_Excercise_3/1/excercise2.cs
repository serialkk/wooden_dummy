public class Ingame : MonoBehavior{
	
	// Use this for initialization
	void Start () {
		object Obj = null;
		
		Obj = Resources.Load("Prefab/sphere");
		GameObject [] m_ObjList = new GameObject[3];
		
		for(int i =0; i <3; i++){
			m_ObjList[i]  = (GameObject)(GameObject.Instantiate(Obj, new Vector3(i*10,0,0),Quaternion.Identity)); 
		}

		
    }

    // Update is called once per frame
    void Update () {

    }
}