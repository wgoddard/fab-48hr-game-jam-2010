using UnityEngine;
using System.Collections;

public class Base : MonoBehaviour {
	
	public Attackable attackable;
	public tk2dSpriteAnimator animator;
	
	public float percent;
	private int frames;
	public int frame;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
		
		percent = 1 - (float)Mathf.Clamp (attackable.currentHP,0, attackable.maxHP) / (float)attackable.maxHP;
		frames = animator.GetClipByName("Destroy").frames.Length;
		frame = (int)(percent * frames);
		frame = Mathf.Clamp (frame, 0, frames - 1);
		//Debug.Log (frame + "length" + animator.GetClipByName("Destroy").frames.Length);
		animator.SetFrame(frame);
	
	}
}
