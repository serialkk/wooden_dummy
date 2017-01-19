public class Ingame : MonoBehavior{
	
 void Awake()
    {
        TPrefabMgr.Load("Prefab", string.Empty);
    }
    // Use this for initialization
    void Start () {
        Object Obj = null;
		
        GameObject [] m_ObjList = new GameObject[3];

        for (int i = 0; i < 3; i++)
        {
            m_ObjList[i] = TPrefabMgr.Instance("Sphere",
                "Obj"+i.ToString(), i * 10, 0, 0);
        }
    }

    // Update is called once per frame
    void Update () {

    }
}