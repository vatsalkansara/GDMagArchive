///////////////////////////////////////////////////////////////////////////////
//
// Skeleton.cpp : Animation System Skeleton supprt file
//
// Purpose:	Structure Supprt routines for Hierarchical Animation System
//
// I DIDN'T PUT THESE IN A C++ CLASS FOR CROSS PLATFORM COMPATIBILITY
// SINCE THE ENGINE MAY BE IMPLEMENTED ON CONSOLES AND OTHER SYSTEMS
//
// Created:
//		JL 9/1/97		
//
///////////////////////////////////////////////////////////////////////////////
//
//	Copyright 1997 Jeff Lander, All Rights Reserved.
//  For educational purposes only.
//  Please do not republish in electronic or print form without permission
//  Thanks - jeffl@darwin3d.com
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "skeleton.h"

///////////////////////////////////////////////////////////////////////////////
// Function:	DestroySkeleton
// Purpose:		Clear memory for a skeletal system
// Arguments:	Pointer to bone system
///////////////////////////////////////////////////////////////////////////////
void DestroySkeleton(t_Bone *root)
{
/// Local Variables ///////////////////////////////////////////////////////////
	int loop;
	t_Bone **child;
///////////////////////////////////////////////////////////////////////////////
	if (root == NULL) return;
	// NEED TO RECURSIVELY GO THROUGH THE CHILDREN
	if (root->childCnt > 0)
	{
		child = root->children;
		for (loop = 0; loop < root->childCnt; loop++)
		{
			if (child[loop]->childCnt > 0)
				DestroySkeleton(child[loop]);
			if (child[loop]->primChannel > NULL)
			{
				free(child[loop]->primChannel);
				child[loop]->primChannel = NULL;
			}
		}
		free(root->children);
	}

	root->primChanType = CHANNEL_TYPE_NONE;
	root->secChanType = CHANNEL_TYPE_NONE;
	root->primFrameCount = 0;
	root->secFrameCount = 0;
	root->primCurFrame = 0;
	root->secCurFrame = 0;
	root->primChannel = NULL;
	root->secChannel = NULL;

	root->CV_select = NULL;					// POINTER TO WEIGHTS
	root->CV_weight = NULL;					// POINTER TO VISUALS
	root->visualCnt = 0;					// COUNT OF ATTACHED VISUAL ELEMENTS
	root->visuals = NULL;					// POINTER TO VISUALS
	root->childCnt = 0;						// COUNT OF ATTACHED BONE ELEMENTS
	root->children = NULL;					// POINTER TO CHILDREN
}
//// DestroySkeleton //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	ResetSkeleton
// Purpose:		Reset a skeletal system
// Arguments:	Pointer to bone system
///////////////////////////////////////////////////////////////////////////////
void ResetSkeleton(t_Bone *bone)
{
/// Local Variables ///////////////////////////////////////////////////////////
	int loop;
	t_Bone **children;
///////////////////////////////////////////////////////////////////////////////
	bone->rot.x = bone->b_rot.x;
	bone->rot.y = bone->b_rot.y;
	bone->rot.z = bone->b_rot.z;

	bone->trans.x = bone->b_trans.x;
	bone->trans.y = bone->b_trans.y;
	bone->trans.z = bone->b_trans.z;

	bone->scale.x = bone->b_scale.x;
	bone->scale.y = bone->b_scale.y;
	bone->scale.z = bone->b_scale.z;

	// NEED TO RECURSIVELY GO THROUGH THE CHILDREN
	if (bone->childCnt > 0)
	{
		children = bone->children;
		for (loop = 0; loop < bone->childCnt; loop++)
		{
			ResetSkeleton(children[loop]);
		}
	}
}
//// ResetSkeleton //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	FreezeSkeleton
// Purpose:		Freeze a skeletal system
// Arguments:	Pointer to bone system
///////////////////////////////////////////////////////////////////////////////
void FreezeSkeleton(t_Bone *bone)
{
/// Local Variables ///////////////////////////////////////////////////////////
	int loop;
	t_Bone **child;
///////////////////////////////////////////////////////////////////////////////
	bone->b_rot.x = bone->rot.x;
	bone->b_rot.y = bone->rot.y;
	bone->b_rot.z = bone->rot.z;

	bone->b_trans.x = bone->trans.x;
	bone->b_trans.y = bone->trans.y;
	bone->b_trans.z = bone->trans.z;

	// NEED TO RECURSIVELY GO THROUGH THE CHILDREN
	if (bone->childCnt > 0)
	{
		child = bone->children;
		for (loop = 0; loop < bone->childCnt; loop++)
		{
			FreezeSkeleton(child[loop]);
		}
	}
}
//// FreezeSkeleton //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	ResetBone
// Purpose:		Reset the bone system and set the parent bone
// Arguments:	Pointer to bone system, and parent bone (could be null)
///////////////////////////////////////////////////////////////////////////////
void ResetBone(t_Bone *bone,t_Bone *parent)
{
	bone->b_scale.x =
	bone->b_scale.y =
	bone->b_scale.z = 1.0;
	bone->scale.x =
	bone->scale.y =
	bone->scale.z = 1.0;

	bone->b_rot.x =
	bone->b_rot.y =
	bone->b_rot.z = 0.0;
	bone->rot.x =
	bone->rot.y =
	bone->rot.z = 0.0;

	bone->b_trans.x =
	bone->b_trans.y =
	bone->b_trans.z = 0.0;
	bone->trans.x =
	bone->trans.y =
	bone->trans.z = 0.0;

	bone->primChanType = CHANNEL_TYPE_NONE;
	bone->secChanType = CHANNEL_TYPE_NONE;
	bone->primFrameCount = 0;
	bone->secFrameCount = 0;
	bone->primCurFrame = 0;
	bone->secCurFrame = 0;
	bone->primChannel = NULL;
	bone->secChannel = NULL;
	bone->animBlend = 0.0f;

	bone->bsphere = 1.0f;
	bone->visualCnt = 0;					// COUNT OF ATTACHED VISUAL ELEMENTS
	bone->visuals = NULL;					// POINTER TO VISUALS
	bone->childCnt = 0;						// COUNT OF ATTACHED BONE ELEMENTS
	bone->children = NULL;					// POINTER TO CHILDREN
	bone->flags = CHANNEL_TYPE_RXYZ;	// ROTATION (RX RY RZ) ORDER
	bone->parent = parent;
	bone->CV_select = NULL;					// POINTER TO WEIGHTS
	bone->CV_weight = NULL;					// POINTER TO VISUALS
}
//// ResetBone ////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	BoneSetFrame
// Purpose:		Set the animation stream for a bone
// Arguments:	Pointer to bone system, frame to set to
///////////////////////////////////////////////////////////////////////////////
void BoneSetFrame(t_Bone *bone,int frame)
{
/// Local Variables ///////////////////////////////////////////////////////////
	float *offset;
///////////////////////////////////////////////////////////////////////////////

	if (bone->primChannel != NULL)
	{
		offset = (float *)(bone->primChannel + (s_Channel_Type_Size[bone->primChanType] * frame));

		// THIS HANDLES THE INDIVIDUAL STREAM TYPES.  ONLY ONE NOW.
		switch (bone->primChanType)
		{
		// TYPE_SRT HAS 9 FLOATS IN TXYZ,RXYZ,SXYZ ORDER
		case CHANNEL_TYPE_SRT:
			bone->trans.x = offset[0];
			bone->trans.y = offset[1];
			bone->trans.z = offset[2];

			bone->rot.x = offset[3];
			bone->rot.y = offset[4];
			bone->rot.z = offset[5];

// I DON'T REALLY WANT MY ANIMATION TO DEAL WITH SCALE RIGHT NOW 
// EVEN THOUGH IT IS IN THE BVA FILE
//			bone->scale.x = offset[6];
//			bone->scale.y = offset[7];
//			bone->scale.z = offset[8];
			break;

		}
	}
}
//// BoneAdvanceFrame /////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	BoneAdvanceFrame
// Purpose:		Increment the animation stream for a bone and possible the
//				children attached to that bone1
// Arguments:	Pointer to bone system, Delta frame value to move, if it is recursive
///////////////////////////////////////////////////////////////////////////////
void BoneAdvanceFrame(t_Bone *bone,int direction,BOOL doChildren)
{
/// Local Variables ///////////////////////////////////////////////////////////
	int loop;
	t_Bone **child;
///////////////////////////////////////////////////////////////////////////////
	// THERE MUST BE SOME THINGS TO ADVANCE 
	if (bone->childCnt > 0)
	{
		child = bone->children;
		for (loop = 0; loop < bone->childCnt; loop++)
		{
			// ADVANCE THE STREAM
			child[loop]->primCurFrame += direction;
			if (child[loop]->primCurFrame >= child[loop]->primFrameCount)
				child[loop]->primCurFrame = 0;
			if (child[loop]->primCurFrame < 0)
				child[loop]->primCurFrame += child[loop]->primFrameCount;
			BoneSetFrame(child[loop],(int)child[loop]->primCurFrame);
			if (doChildren && child[loop]->childCnt > 0)				// IF THIS CHILD HAS CHILDREN
				BoneAdvanceFrame(child[loop],direction,doChildren);	// RECURSE DOWN HIER
		}
	}
}
//// BoneAdvanceFrame /////////////////////////////////////////////////////////////////

// Utility function to get a certain numbered word from a string
void GetWord(char *string, int wordNum, char *word)
{
/// Local Variables ///////////////////////////////////////////////////////////
	char *thisword = string, *nextword;
	int  begin, end, i;
///////////////////////////////////////////////////////////////////////////////
	word[0] = 0;
	for (i = 0; i < wordNum - 1; i++)
	{
		nextword = strstr(thisword," ");
		thisword = nextword;
		if (thisword) 
			while (strlen(thisword) > 0 && *thisword == ' ') thisword++;
	}
	begin = thisword - string;
	nextword = strstr(thisword," ");
	if (nextword == NULL)
		end = strlen(string);
	else
		end = nextword - string;
	memcpy(word,&string[begin],end - begin);
	word[end - begin] = 0;
	for (i = 0; i < strlen(word); i++)
		if (word[i] == 10 || word[i] == 12)
			word[i] = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function:	LoadD3DSkeleton
// Purpose:		Load D3D Skeleton File format
// Arguments:	Pointer to bone system, file name
///////////////////////////////////////////////////////////////////////////////
BOOL LoadD3DSkeleton(t_Bone **root,char *name,int *boneCnt,t_Visual *visual)
{
/// Local Variables ///////////////////////////////////////////////////////////
	t_Bone	*bone,**child,*base;
	FILE	*fp;
	char	buffer[2048],temp[80];
	int id = 0,weightcnt;
///////////////////////////////////////////////////////////////////////////////
	*boneCnt = 0;
	if (*root) 
	{
		DestroySkeleton(*root);
		free(*root);
	}

	fp = fopen(name,"r");

	if (!fp) return FALSE;	// Couldn't open file

	// First count the bones
	while (!feof(fp))
	{
		fgets(buffer,2048,fp);
		if (strncmp(buffer,"Bone",4) == 0) *boneCnt = *boneCnt + 1;
	}
	fseek(fp,0,SEEK_SET);	// Back to the top of the file

	if (*boneCnt > 0)
	{
		*root = (t_Bone *)malloc(sizeof(t_Bone) * *boneCnt);
		bone = *root;
		while (!feof(fp))
		{
			fgets(buffer,2048,fp);
			if (strncmp(buffer,"Bone",4) == 0)
			{
				ResetBone(bone,NULL);
				bone->id = id++;
				sscanf(buffer,"%s %s",temp,bone->name);	// Get the current bone name
				fgets(buffer,2048,fp);					// {
				fgets(buffer,2048,fp);					// Childcnt
				bone->childCnt = atoi(buffer);
				if (bone->childCnt > 0)					// Get the names of the children
				{
					bone->children = (t_Bone **)malloc(sizeof(t_Bone *) * bone->childCnt);
					bone->parent = (t_Bone *)malloc(2048);		// Temp storage for heirarchy
					fgets((char *)bone->parent,2048,fp);				// Hierarchy line
				}
				fgets(buffer,2048,fp);					// translation line
				GetWord(buffer,1,temp);
				bone->b_trans.x = atof(temp);
				GetWord(buffer,2,temp);
				bone->b_trans.y = atof(temp);
				GetWord(buffer,3,temp);
				bone->b_trans.z = atof(temp);

				fgets(buffer,2048,fp);					// rotation line
				GetWord(buffer,1,temp);
				bone->b_rot.x = atof(temp);
				GetWord(buffer,2,temp);
				bone->b_rot.y = atof(temp);
				GetWord(buffer,3,temp);
				bone->b_rot.z = atof(temp);

				fgets(buffer,2048,fp);					// scale line
				GetWord(buffer,1,temp);
				bone->b_scale.x = atof(temp);
				GetWord(buffer,2,temp);
				bone->b_scale.y = atof(temp);
				GetWord(buffer,3,temp);
				bone->b_scale.z = atof(temp);

				fgets(buffer,2048,fp);					// bsphere line
				bone->bsphere = atof(buffer);
				
				// Reset all weights to 0 after they are allocated
				if (visual->vertexCnt > 0)
				{
					bone->CV_weight = (t_VWeight *)malloc(sizeof(t_VWeight) * visual->vertexCnt);
					for (int j = 0; j < visual->vertexCnt; j++)
					{
						bone->CV_weight[j].vertex = j;
						bone->CV_weight[j].weight = 0.0f;
					}
				}
				// Load weight settings
				fgets(buffer,2048,fp);					// weight line
				sscanf(buffer,"%s %d",temp,&weightcnt);	
				if (strncmp(temp,"weights",7) == 0)
				{
					if (weightcnt > 0)
					{
						for (int i = 0; i < weightcnt; i++)
						{
							fgets(buffer,2048,fp);					// actual weight
							int v;
							float w;
							sscanf(buffer,"%d %f",&v,&w);	// Get the current bone name
							if (visual->vertexCnt > 0 && v < visual->vertexCnt)
							{
								bone->CV_weight[v].weight = w;
							}
						}
					}
					fgets(buffer,2048,fp);					// }
				}
				bone++;									// Finished this bone
			}
		}

		// Finished loading the bones, now fixup the child pointer
		base = bone = *root;
		for (int i = 0; i < *boneCnt; i++,bone++)
		{
			child = bone->children;
			for (int c = 0; c < bone->childCnt; c++)	// Go through each child
			{
				GetWord((char *)bone->parent,c + 1,temp);		// Get the Name of the child
				for (int b = 0; b < *boneCnt; b++)
				{
					if (strcmp(temp,base[b].name) == 0)		// found a match
					{
						child[c] = &base[b];
						break;
					}
				}
			}
			free(bone->parent);
			bone->parent = NULL;	// Not using parent
		}
		ResetSkeleton(*root);
	}
	fclose(fp);
	return TRUE;
}
//// LoadD3DSkeleton /////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	SaveD3DSkeleton
// Purpose:		Save D3D Skeleton File format
// Arguments:	Pointer to bone system, file name
///////////////////////////////////////////////////////////////////////////////
BOOL SaveD3DSkeleton(t_Bone **root,char *name,int boneCnt,t_Visual *visual)
{
/// Local Variables ///////////////////////////////////////////////////////////
	t_Bone	*bone;
	FILE	*fp;
	int id = 0;
///////////////////////////////////////////////////////////////////////////////
	fp = fopen(name,"w");

	if (!fp) return FALSE;	// Couldn't open file

	if (boneCnt > 0)
	{
		bone = *root;
		for (int bnum = 0; bnum < boneCnt; bnum++)
		{

			fprintf(fp,"Bone %s\n{\n",bone->name);
			fprintf(fp,"%d\n",bone->childCnt);
			if (bone->childCnt > 0)					// Get the names of the children
			{
				for (int i = 0; i < bone->childCnt; i++)
				{
					fprintf(fp,"%s  ",bone->children[i]->name);
				}
				fprintf(fp,"\n");
			}
			fprintf(fp,"%.4f  %.4f  %.4f\n",bone->b_trans.x,bone->b_trans.y,bone->b_trans.z);
			fprintf(fp,"%.4f  %.4f  %.4f\n",bone->b_rot.x,bone->b_rot.y,bone->b_rot.z);
			fprintf(fp,"%.4f  %.4f  %.4f\n",bone->b_scale.x,bone->b_scale.y,bone->b_scale.z);

			fprintf(fp,"%.4f\n",bone->bsphere);

			int wcnt = 0;
			// Count up all non-zero weights
			for (int i = 0; i < visual->vertexCnt; i++)
			{
				if (bone->CV_weight[i].weight > 0.0f) wcnt++;
			}
			// Write non-zero weights to file
			fprintf(fp,"weights %d\n",wcnt);
			for (i = 0; i < visual->vertexCnt; i++)
			{
				if (bone->CV_weight[i].weight > 0.0f)
				{
					fprintf(fp,"%d %.4f\n",i,bone->CV_weight[i].weight);
				}
			}

			fprintf(fp,"}\n");
			bone++;									// Finished this bone
		}

	}
	fclose(fp);
	return TRUE;
}
//// SaveD3DSkeleton /////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	LoadD3DPose
// Purpose:		Load D3D Skeleton File format
// Arguments:	Pointer to bone system, file name
///////////////////////////////////////////////////////////////////////////////
BOOL LoadD3DPose(t_Bone **root,char *name,int boneCnt,t_Visual *visual)
{
/// Local Variables ///////////////////////////////////////////////////////////
	t_Bone	*bone;
	FILE	*fp;
	char	buffer[2048],temp[80];
	int id = 0,weightcnt;
///////////////////////////////////////////////////////////////////////////////
	fp = fopen(name,"r");

	if (!fp) return FALSE;	// Couldn't open file

	if (boneCnt > 0)
	{
		bone = *root;
		for (int bnum = 0; bnum < boneCnt; bnum++)
		{
			fgets(buffer,2048,fp);
			if (strncmp(buffer,"Bone",4) == 0)
			{
				fgets(buffer,2048,fp);					// {
				fgets(buffer,2048,fp);					// Childcnt
				if (bone->childCnt > 0)					// Get the names of the children
				{
					fgets(buffer,2048,fp);				// Hierarchy line
				}
				fgets(buffer,2048,fp);					// translation line
				GetWord(buffer,1,temp);
				bone->trans.x = atof(temp);
				GetWord(buffer,2,temp);
				bone->trans.y = atof(temp);
				GetWord(buffer,3,temp);
				bone->trans.z = atof(temp);

				fgets(buffer,2048,fp);					// rotation line
				GetWord(buffer,1,temp);
				bone->rot.x = atof(temp);
				GetWord(buffer,2,temp);
				bone->rot.y = atof(temp);
				GetWord(buffer,3,temp);
				bone->rot.z = atof(temp);

				fgets(buffer,2048,fp);					// scale line
				GetWord(buffer,1,temp);
				bone->scale.x = atof(temp);
				GetWord(buffer,2,temp);
				bone->scale.y = atof(temp);
				GetWord(buffer,3,temp);
				bone->scale.z = atof(temp);

				fgets(buffer,2048,fp);					// bsphere line
				fgets(buffer,2048,fp);					// weight line
				sscanf(buffer,"%s %d",temp,&weightcnt);	
				if (weightcnt > 0 && weightcnt == visual->vertexCnt)
				{
					for (int i = 0; i < weightcnt; i++)
					{
						fgets(buffer,2048,fp);					// actual weight
					}
				}

				fgets(buffer,2048,fp);					// }
				bone++;									// Finished this bone
			}
		}

	}
	fclose(fp);
	return TRUE;
}
//// LoadD3DPose /////////////////////////////////////////////////////////////////
