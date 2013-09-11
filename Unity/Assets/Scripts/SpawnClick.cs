using UnityEngine;
using System.Collections;

public class SpawnClick : MonoBehaviour {
	
	public tk2dUIItem button;
	public GameObject spawnPrefab;
	public GameObject spawnLocation;
	public Resource resourceSource;
	
	private Character spawnCode;

	// Use this for initialization
	void Start () {
		
		if (spawnPrefab != null) {
			spawnCode = spawnPrefab.GetComponent("Character") as Character;
		}
	
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
		if (resourceSource.resourceCount >= spawnCode.spawnCost) {
			resourceSource.resourceCount -= spawnCode.spawnCost;
	        GameObject spawned = GameObject.Instantiate (spawnPrefab) as GameObject;
			spawned.transform.position = spawnLocation.transform.position;
		}
    }

}
