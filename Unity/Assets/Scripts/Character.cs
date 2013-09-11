using UnityEngine;
using System.Collections;

public class Character : MonoBehaviour {
	
	public int spawnCost = 1;
	public float speed = 30.0f;
	
	private tk2dSpriteAnimator animator;

	// Use this for initialization
	void Start () {
		
		animator = GetComponent("tk2dSpriteAnimator") as tk2dSpriteAnimator;
		
		animator.Play("Walk");

		
		//transform.position = new Vector3(transform.position.x, transform.position.y, transform.position.y/20.0f);
	
	}
	
	// Update is called once per frame
	void Update () {
		
		float adjustedSpeed = speed / 20.0f;
		
		transform.position = new Vector3(transform.position.x + Time.deltaTime * adjustedSpeed, transform.position.y, transform.position.y/20.0f);
	
	}
}
