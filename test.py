
print " __QUESTIONNAIRE__\n  Etes vous fait pour l'informatique ?"
age = input("\nQuel est votre age : ")
nom = raw_input("Quel est votre nom : ")
if nom.lower().startswith("max"):
	print "\n --> Vous etes fait pour l'informatique !"
else:
	print "\n --> Il va falloir bosser dur."
