using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class PuzzleNodeScript : MonoBehaviour
{
    public bool IMadeChildren = false;
    public int Gn = 0, Hn = 0, Fn = 0;
    public List<GameObject> next = new List<GameObject>();
    public int[] config = new int[9];
    public TextMeshProUGUI GVal, HVal, FVal;
    public List<GameObject> prefabTiles = new List<GameObject>();
    public List<GameObject> myTiles = new List<GameObject>();
    // Start is called before the first frame update
    private List<Vector3> availableTilePos;
    void Awake()
    {
        SetupTilePosDict();
    }
    void Update()
    {

    }
    //For each position on the board,
    // this function cycles through the entire myTiles list
    // looking for it's value. If theres a match at that position,
    // config's value becomes that tile's value at that position,
    // otherwise config's value because zero at that position in the config list.
    public void RootMakeConfigList()
    {
        for (int i = 0; i < 9; ++i) {
            bool foundTile = false;
            for (int j = 0; j < 8; ++ j) {
                if (myTiles[j] != null) {
                    if (availableTilePos[i] == myTiles[j].transform.position) {
                        TileScript thisTileScript = myTiles[j].GetComponent<TileScript>();
                        config[i] = (int) thisTileScript.myNumberValue;
                        foundTile = true;
                    }
                }
            }
            if (!foundTile)
                config[i] = 0;
        }
    }
    public void SetupTilePosDict()
    {
        availableTilePos = new List<Vector3>() {
            new Vector3(this.transform.position.x-1,this.transform.position.y+1, 0),
            new Vector3(this.transform.position.x+0,this.transform.position.y+1, 0),
            new Vector3(this.transform.position.x+1,this.transform.position.y+1, 0),
            new Vector3(this.transform.position.x-1,this.transform.position.y+0, 0),
            new Vector3(this.transform.position.x+0,this.transform.position.y+0, 0),
            new Vector3(this.transform.position.x+1,this.transform.position.y+0, 0),
            new Vector3(this.transform.position.x-1,this.transform.position.y-1, 0),
            new Vector3(this.transform.position.x+0,this.transform.position.y-1, 0),
            new Vector3(this.transform.position.x+1,this.transform.position.y-1, 0)
        };
    }
    public void UpdateHVal(int newHVal)
    {
        Hn = newHVal;
        HVal.text = "H(n) = " + Hn.ToString();
        Fn = Gn+Hn;
        FVal.text = "F(n) = " + Fn.ToString();
    }
    public void SetGVal(int newGval)
    {
        Gn = newGval;
        GVal.text = "G(n) = " + Gn.ToString();
        Fn = Gn+Hn;
        FVal.text = "F(n) = " + Fn.ToString();
    }
    //Locates the next number on the config list
    //Creates a prefab tile of that value, in the position from the array
    public void SetUpTiles()
    {
        int zeroadj = 1;
        for (int i = 0; i < 9; ++i) {
            int tileVal = config[i];
            if (tileVal > 0) {
                GameObject newTile = Instantiate(prefabTiles[tileVal-zeroadj], availableTilePos[i], Quaternion.identity) as GameObject;
                TileScript newTileScript = newTile.GetComponent<TileScript>();
                newTileScript.Init(this.gameObject);
                myTiles.Add(newTile);
            }
        } 
    }
    public void SetUpConfig(int[] newConfigList)
    {
        config = new int[9];
        for (int i = 0; i < 9; ++i)
            config[i] = newConfigList[i];
    }
}
