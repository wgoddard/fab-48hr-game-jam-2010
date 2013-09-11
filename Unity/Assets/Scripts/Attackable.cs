using UnityEngine;
using System.Collections;

public class Attackable : MonoBehaviour {
	
	public int currentHP;
	public int maxHP = 5;

	// Use this for initialization
	void Start () {
			currentHP = maxHP;
	}
	
	// Update is called once per frame
	void Update () {
		
		if (currentHP < 0) {
			//currentHP = 0;
		}
	
	}
	
	public bool IsAlive() {
		return currentHP >= 0;
	}
}
