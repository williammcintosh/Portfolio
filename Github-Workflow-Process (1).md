
# Setup Github w/ Project:

This only needs to be done once per project.

1. Download data from source
2. Open VS Code and navigate to the folder containing your code files.
3. Open the integrated terminal in VS Code by going to View -> Terminal or using the shortcut Ctrl+`.
4. Initialize a new Git repository by running the command `git init`. This will create a new local repository.
5. Next, create a new repository on GitHub. Go to the GitHub website, log in, and click on the "New" button to create a new repository. Give it a name and choose whether you want it to be public or private.
6. Once the repository is created, copy the SSH URL of the repository from the GitHub website.
7. In the terminal, add the remote repository by running the command `git remote add origin <SSH_URL>`. Replace `<SSH_URL>` with the SSH URL you copied in the previous step.
8. Now, you can add all your code files to the repository by running the command `git add .`
   * This will stage all the files for commit.
9. Commit the changes by running the command `git commit -m "Initial commit"`.
10. Finally, push the code to the remote repository by running the command `git push -u origin main`. This will push the code to the master branch of the remote repository.
    * You might need to call the branch `master` intead.
    * Or, `git remote rename origin homework`
   

Or simplified:

1. Create a new repository on GitHub. Go to the GitHub website, log in, and click on the "New" button to create a new repository. Give it a name and choose whether you want it to be public or private.
2. Copied the ssh line
3. Create a folder
4. Run the command `git clone git@github.com:williammcintosh/CS510_CRR.git .`
    * Alternatively `git clone git@github.com:williammcintosh/CS510_CRR.git <name_of_folder>`


# Working with a Private Repo

To make the repository private and give yourself access rights using an SSH key, follow these steps:

1. Generate an SSH key pair if you haven't already. You can do this by running the command `ssh-keygen` in the terminal. Follow the prompts to generate the key pair.
2. Add the SSH key to your GitHub account. Go to the GitHub website, log in, and navigate to your account settings. Under "SSH and GPG keys", click on "New SSH key" and paste the contents of your public key file (~/.ssh/id_rsa.pub).
3. In the terminal, change the remote URL to use SSH instead of HTTPS by running the command `git remote set-url origin <SSH_URL>`. Replace `<SSH_URL>` with the SSH URL of your repository.
4. Now, you can push your code to the remote repository using SSH by running the command `git push -u origin master`.


# Github Workflow

This example names branches by my initials `WMM` + the branch number in the project.

1. create and name a branch `git checkout -b WMM001`
2. Perform work on the actual code files
3. Move files: Working Directory $\rightarrow$ Staging Area `git add .`
4. Move files: Staging Area $\rightarrow$ Local Repo  `git commit -m "did some stuff"`
5. Move files: Local Repo $\rightarrow$ Remote Repo  `git push -u origin WMM001`
  * This goes specifically to the branch you're working on
6. Change to the main branch `git checkout main`
7. Merge your work from the branch to main branch `git merge WMM001`
8. Push work to main `git push -u origin main`


# Pretty Print

To make the graph pretty, edit the .gitconfig file on your device:

1. Run the command `vim ~/.gitconfig`
2. Add the following lines at the bottom:
   * ```
     [alias]
        lg1 = log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)' --all
        lg2 = log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(auto)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)'
        lg = lg1
     ```
3. Save the file.
4. When you want to print the graph run one of the following commands:
    * `git lg`
    * `git lg1`
    * `git lg2` $\leftarrow$ my personal favorite
  
