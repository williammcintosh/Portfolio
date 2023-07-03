
# Setting Up SSH

To make the repository private and give yourself access rights using an SSH key, follow these steps:

1. Generate an SSH key pair if you haven't already. You can do this by running the command `ssh-keygen` in the terminal. Follow the prompts to generate the key pair.
2. Add the SSH key to your GitHub account. Go to the GitHub website, log in, and navigate to your account settings. Under "SSH and GPG keys", click on "New SSH key" and paste the contents of your public key file (~/.ssh/id_rsa.pub).
3. In the terminal, change the remote URL to use SSH instead of HTTPS by running the command `git remote set-url origin <SSH_URL>`. Replace `<SSH_URL>` with the SSH URL of your repository.


# Setup Github w/ Project:

This only needs to be done once per project.

1. Download data from source (provided by professor?)
2. Open VS Code and navigate to the folder containing your code files.
    * Make sure this **is not** the parent folder, but instead only open the highest, loal working directory.
3. Open the integrated terminal in VS Code by going to View -> Terminal or using the shortcut Ctrl+`.
4. Create a new **remote** repository on GitHub. Go to the GitHub website, log in, and click on the "New" button to create a new repository. Give it a name and choose whether you want it to be public or private.
5. Once the repository is created, copy the SSH URL of the repository from the GitHub website.
6. Run the command `git clone <SSH_URL> .`
    * Alternatively `git clone <SSH_URL> <name_of_folder_defaults_to_repo_name>`
    * This requires you to have setup your SSH locally (See steps above)


# Github Workflow

This example names branches by my initials `WMM/` + small_description_of_your_work_without_spaces. For example, `WMM/Update-Bio`. Also, between each step, be sure to run `git status` to know where your work is throughout the process.

1. Create and name a branch `git checkout -b WMM/Update-Bio`
   * This creates a branch **based on the current branch**.
2. Perform work on the actual code and files, or add images.
3. Update Git Tracking: Working Directory $\rightarrow$ Staging Area `git add .`
4. Update Git Tracking: Staging Area $\rightarrow$ Local Repo  `git commit -m "did some stuff"`
   * Commit is saying that you are putting this list of changes into the current branch, and that branch will now have a commit SHA that points to those changes.
5. Update Git Tracking: Local Repo $\rightarrow$ Remote Repo  `git push`

   * This will actually fail like this:
   ```
   ⦻ (base) willmcintosh@Wills-MacBook-Pro hw1 % git push 
    fatal: The current branch WMM/Update-Bio has no upstream branch.
    To push the current branch and set the remote as upstream, use
    
        git push --set-upstream origin WMM/Update-Bio
    
    To have this happen automatically for branches without a tracking
    upstream, see 'push.autoSetupRemote' in 'git help config'.
   ```
   * Copy this line of code and run command `git push --set-upstream origin WMM/Update-Bio`
6. This will out put the lines below:
   ```
   (base) willmcintosh@Wills-MacBook-Pro calculator-main % git push --set-upstream origin WMM/Update-Bio
   Enumerating objects: 21, done.
   Counting objects: 100% (21/21), done.
   Delta compression using up to 8 threads
   Compressing objects: 100% (17/17), done.
   Writing objects: 100% (20/20), 8.13 KiB | 489.00 KiB/s, done.
   Total 20 (delta 0), reused 0 (delta 0), pack-reused 0
   remote: 
   remote: Create a pull request for 'WMM/Update-Bio' on GitHub by visiting:
   remote:      https://github.com/williammcintosh/CS510_CRR/pull/new/WMM/Update-Bio
   remote: 
   To github.com:williammcintosh/CS510_CRR.git
    * [new branch]      WMM/Update-Bio -> WMM/Update-Bion
   branch 'WMM/Update-Bio' set up to track 'origin/WMM/Update-Bio'.
   ```
   * Hold Command and click on the url inside `https://github.com/williammcintosh/CS510_CRR/pull/new/WMM/Update-Bio`
7. Follow the prompts in the Github website. Add comments -> Create Pull Request. Merge Pull Request. Confirm Merge.
8. Update local repo by running this command `git checkout main; git fetch --all; git pull`.

Also, did you accidentally finish all the steps above and later realized that you missed something in that branch? Amend to the rescue!

1. Do your work on the code / file management.
2. Run the command `git commit --amend`.
3. Force push the new changes `git push -f`.


# Pretty Print

To make the graph pretty, edit the .gitconfig file on your device:

1. Run the command `vim ~/.gitconfig`
2. Add the following lines at the bottom:
   ```
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
  
