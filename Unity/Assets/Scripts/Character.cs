using UnityEngine;
using System.Collections;

public class Character : MonoBehaviour {
	
	public int spawnCost = 1;
	public float speed = 30.0f;
	public float range = 8.0f;
	public int damage = 1;
	public Attackable attackable;
	
	public enum AttackType { Ranged, SingleMelee, MultiMelee };
	public AttackType attackType = AttackType.SingleMelee;
	
	private GameObject target = null;
	private float attackCooldown;
	private float attackTime;
	
	
	public enum CharacterState { Walking, Engaging, Attacking, Dying };
	public CharacterState state;
	
	
	private tk2dSpriteAnimator animator;

	// Use this for initialization
	void Start () {
		
		if (attackable == null) {
			attackable = GetComponent ("Attackable") as Attackable;
		}
		
		animator = GetComponent("tk2dSpriteAnimator") as tk2dSpriteAnimator;
		
		Walk ();

		
		//transform.position = new Vector3(transform.position.x, transform.position.y, transform.position.y/20.0f);
	
	}
	
	void Walk() {
		animator.Play("Walk");
		state = CharacterState.Walking;
	}
	
	void Engage (GameObject _target) {
		target = _target;
		state = CharacterState.Engaging;
	}
	
	void Attack (GameObject _target) {
		if (state == CharacterState.Dying) {
			Debug.Log ("Warning! Character dead! Cannot attack");
		}
		
		target = _target;
		state = CharacterState.Attacking;
		tk2dSpriteAnimationClip clip = animator.GetClipByName ("Attack");
		animator.Play(clip);
		attackTime = clip.frames.Length / clip.fps;
		attackCooldown = attackTime;
	}
	
	void Die() {
		
		state = CharacterState.Dying;
		animator.Play ("Die");
		animator.CurrentClip.wrapMode = tk2dSpriteAnimationClip.WrapMode.Once;
		animator.AnimationCompleted += CleanUp;
		
		//last chance attack
		if (target == null) {
			
		} else {
			attackCooldown -= Time.deltaTime;
			if (attackCooldown < 0.1f) {
				//do damage
				attackCooldown = attackTime;
				DamageTarget ();
			}
		}
		
	}
	
	void CleanUp(tk2dSpriteAnimator animator, tk2dSpriteAnimationClip clip) {
		animator.AnimationCompleted -= CleanUp;
		Destroy (gameObject);
	}
	
	bool IsTargetValid() {
		if (target == null) {
			return false;
		}
		Attackable c = target.GetComponent ("Attackable") as Attackable;
		return c.IsAlive();
	}
	
	void DamageTarget() {
		Attackable enemy = target.GetComponent ("Attackable") as Attackable;
		enemy.currentHP -= damage;
	}
	
	// Update is called once per frame
	void Update () {
	
		RaycastHit hitInfo;
		
		switch (state) {
			
		case CharacterState.Walking:
			if (!IsTargetValid()) {
			
				Vector3 direction;
				if (CompareTag ("Dino") ) {
					direction = Vector3.right;
				} else {
					direction = Vector3.left;
				}
				if (Physics.Raycast(transform.position, direction, out hitInfo, range) && hitInfo.transform.tag != tag) {
					if (attackType == AttackType.Ranged) {
						Attack (hitInfo.transform.gameObject);
					} else {
						Engage (hitInfo.transform.gameObject);
					}
				}
			} 
			break;
		case CharacterState.Engaging:
			if (!IsTargetValid()) {
				Walk ();
			} else {
				float yDelta = transform.position.y - target.transform.position.y;
				
				if (yDelta > 0.1f) {
					transform.position = new Vector3(transform.position.x, transform.position.y + Mathf.Sign(yDelta) * Time.deltaTime * -100.0f / 20.0f, transform.position.z);
				}
			}
			break;
		case CharacterState.Attacking:	
			if (!IsTargetValid()) {
				Walk ();
			} else {
				attackCooldown -= Time.deltaTime;
				if (attackCooldown < 0.0f) {
					//do damage
					attackCooldown = attackTime;
					DamageTarget();
				}
			}
			break;
		}
		
		if (!attackable.IsAlive() && state != CharacterState.Dying) {
			Die();
		}
		
	}
	
	void FixedUpdate () {
		
		switch (state) {
		case CharacterState.Walking:
			goto case CharacterState.Engaging;
		case CharacterState.Engaging:
			float adjustedSpeed = speed / 20.0f;		
			transform.position = new Vector3(transform.position.x + Time.deltaTime * adjustedSpeed, transform.position.y, (transform.position.y - 1.0f)/20.0f);
			break;
		}
		
	}
	
	void OnTriggerEnter (Collider c) {

		switch (state) {
		case CharacterState.Attacking:
			break;
		case CharacterState.Engaging:
			if ( !c.CompareTag(tag)) {
				Attack (c.gameObject);
			}
			break;
		case CharacterState.Walking: 
			//if collision after walking, probably ranged dude shouldn't be attacking
			if (attackType != AttackType.Ranged && !c.CompareTag(tag)) {
				Attack (c.gameObject);
			}
			break;
		default:
			break;
		}
	}
	
	void OnTriggerStay (Collider c) {
		
		switch (state) {
		
		case CharacterState.Attacking:				
			if (!c.CompareTag(tag)) {
				if (target == null && attackType != AttackType.Ranged) {
					Attack (c.gameObject);
				}
			}
			break;
		}
	}
}
