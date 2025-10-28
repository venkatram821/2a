#  Simple Social Media CLI (DSA Project in C)

This project is a **Data Structures and Algorithms (DSA)** assignment implemented fully in **C language**.  
It simulates a miniature **social media platform** that runs entirely in the **command line** (CLI).

The program demonstrates the use of **linked lists**, **dynamic memory management**, and **modular C programming**.

---


##  how to run code
command : make
To run code : .\social_media


## Overview

The system allows users to:

- Create a new social media platform instance  
- Add, view, and delete **posts**
- Add, view, and delete **comments** on posts  
- Add, view, and delete **replies** to comments  
- Navigate between posts (next, previous, current)
- View a **history of all viewed posts**
- Cleanly free all allocated memory at exit  

Each data type (Post, Comment, Reply) is stored as a **linked list node**, and memory is allocated dynamically.

---

##  Features

| Feature | Description |
|----------|--------------|
| **Create Platform** | Initializes the entire social media platform |
| **Add Post** | Adds a post with a username and caption |
| **View Post** | Views a specific post by index |
| **Delete Post** | Deletes a post and its comments/replies |
| **Add Comment** | Adds a comment to the currently viewed post |
| **View Comments** | Displays all comments and replies for the viewed post |
| **Add Reply** | Adds a reply to a specific comment |
| **Delete Reply** | Deletes a reply from a specific comment |
| **History** | Shows all posts that have been viewed in this session |

---

##  File Structure

