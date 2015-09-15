

/*
void SubString(const char* original, const char* newStr)
{
	if(original == NULL || newStr == NULL) { return; }
	
	unsigned int size_original = strlen(original);
	unsigned int size_new = strlen(newStr);
	
	for (unsigned int i = 0; i < size; i++)
	{
		if(str[i] == original[0])
		{
			// comprobar espacio anterior
			if(i == 0 || str[i - 1] == ' ')
			{
				if(i + size_original < size)
				{
					bool same = true;
					
					unsigned int j = 1;
				
					for(; j < size_original; j++)
					{
						if(str[i + j] != original[j])
						{
							i+=j;
							same = false;
							break;
						}
					}
					if(same)
					{
						// comprobar espacio anterior
						if(i + size_original >= size || str[i + size_original] == ' ')
						{
							if(size_new - size_original > 0)
							{
								Alloc(size + size_new - size_original + 1);
							}
							if(size_original != size_new)
							{
								for (unsigned int k = size; k > i; k--)
								{
									str[k] = str[k - (size_new - size_original)];
								}
							}
							for (unsigned int k = 0; k < size_original; k++)
							{
								str[i + k] = original[k];
							}
						}
						i+=j;
					}	
				}
				else
				{
					return;
				}
			}
		}
	}
	
	
	
	
	
	
	
}




*/




