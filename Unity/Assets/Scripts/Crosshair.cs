using UnityEngine;
using System.Collections;

/// <summary>
/// UIItem you wish be able to drag on press
/// </summary>
[AddComponentMenu("2D Toolkit/UI/tk2dUIDragItem")]
public class Crosshair : tk2dUIBaseItemControl
{
    /// <summary>
    /// Active tk2dUIManager in scene
    /// </summary>
    public tk2dUIManager uiManager = null;
	
	public GameObject crosshairGraphic = null;
	public enum Mode { Starting, Moving, Targeting };
	
	private Mode mode;
	private Vector3 touchStart;
	
    private Vector3 offset = Vector3.zero; //offset on touch/click
    private bool isBtnActive = false; //if currently active

    void OnEnable()
    {
        if (uiItem)
        {
            uiItem.OnDown += ButtonDown;
            uiItem.OnRelease += ButtonRelease;
        }
    }

    void OnDisable()
    {
        if (uiItem)
        {
            uiItem.OnDown -= ButtonDown;
            uiItem.OnRelease -= ButtonRelease;
        }

        if (isBtnActive)
        {
            if (tk2dUIManager.Instance != null)
            {
                tk2dUIManager.Instance.OnInputUpdate -= UpdateBtnPosition;
            }
            isBtnActive = false;
        }
    }

    private void UpdateBtnPosition()
    {
		Vector2 pos = uiItem.Touch.position;
		Vector3 touchCurrent = tk2dUIManager.Instance.UICamera.ScreenToWorldPoint(new Vector3(pos.x, pos.y, transform.position.z - tk2dUIManager.Instance.UICamera.transform.position.z));
		Vector3 difference = touchCurrent - touchStart;
		float magnitude = difference.sqrMagnitude;
		
		switch (mode) {
		case Mode.Starting:
					
			//do nothing until
			if (magnitude > 3 && Mathf.Abs (difference.y) > Mathf.Abs (difference.x) ) {
				offset = Vector3.zero;
				mode = Mode.Moving;
			} else if (magnitude > 3) {
				offset = Vector3.zero;
				mode = Mode.Targeting;
			} else {//not moving/aiming, still waiting
			}
			break;
		case Mode.Moving:
			transform.position = new Vector3(transform.position.x, Mathf.Clamp (CalculateNewPos().y, -20, 0), transform.position.z);
			
			if (Mathf.Min (Mathf.Abs (difference.x), Mathf.Abs (difference.y)) > 2 && Mathf.Abs (difference.x) > Mathf.Abs (difference.y) ) {
				offset = Vector3.zero;
				mode = Mode.Targeting;
			}
			
			break;
		case Mode.Targeting:
			Vector3 targetPos = CalculateNewPos();
			crosshairGraphic.transform.position = new Vector3(targetPos.x, targetPos.y, targetPos.z);
			break;
		}
    }

    private Vector3 CalculateNewPos()
    {
        Vector2 pos = uiItem.Touch.position;

        Vector3 worldPos = tk2dUIManager.Instance.UICamera.ScreenToWorldPoint(new Vector3(pos.x, pos.y, transform.position.z - tk2dUIManager.Instance.UICamera.transform.position.z));
        worldPos.z = transform.position.z;
        worldPos += offset;
        return worldPos;
    }
	
	public void ResetCrosshairPos() {
		crosshairGraphic.transform.localPosition = Vector3.zero;
	}

    /// <summary>
    /// Set button to be down (drag can begin)
    /// </summary>
    public void ButtonDown()
    {
        if (!isBtnActive)
        {
            tk2dUIManager.Instance.OnInputUpdate += UpdateBtnPosition;
			mode = Mode.Starting;
			Vector2 pos = uiItem.Touch.position;
			touchStart = tk2dUIManager.Instance.UICamera.ScreenToWorldPoint(new Vector3(pos.x, pos.y, transform.position.z - tk2dUIManager.Instance.UICamera.transform.position.z));
        }
        isBtnActive = true;
    }

    /// <summary>
    /// Set button release (so drag will stop)
    /// </summary>
    public void ButtonRelease()
    {
        if (isBtnActive)
        {
            tk2dUIManager.Instance.OnInputUpdate -= UpdateBtnPosition;
        }
        isBtnActive = false;
		ResetCrosshairPos ();
    }

}
