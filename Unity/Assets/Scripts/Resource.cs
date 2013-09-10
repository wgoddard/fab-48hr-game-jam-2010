using UnityEngine;
using System.Collections;

public class Resource : MonoBehaviour {
	
	public float resourceTick = 0.5f;
	public int resourceCount = 0;
	public tk2dTextMesh textOutput;
	
	private float countDown;

	// Use this for initialization
	void Start () {
		
		countDown = resourceTick;
	
	}
	
	// Update is called once per frame
	void Update () {
		
		countDown -= Time.deltaTime;
		if (countDown < 0.0f) {
			countDown = resourceTick;
			resourceCount++;
		}
		textOutput.text = resourceCount.ToString ();
		textOutput.Commit();
	
	}
}
