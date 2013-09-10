using UnityEngine;
using System.Collections;

public class SpawnClick : MonoBehaviour {
	
	public tk2dUIItem button;
	public GameObject spawnPrefab;
	public GameObject spawnLocation;
	public Resource resourceSource;

	// Use this for initialization
	void Start () {
		
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
    void OnEnable()
    {
        if (button)
        {
            button.OnClick += Spawn;
        }
    }

    void OnDisable()
    {
        if (button)
        {
            button.OnClick -= Spawn;
        }
    }

    private void Spawn()
    {
        GameObject spawned = GameObject.Instantiate (spawnPrefab) as GameObject;
		spawned.transform.position = spawnLocation.transform.position;
    }

}
