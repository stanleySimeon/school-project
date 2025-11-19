# Quick Deployment Guide

## ✅ Easiest Option: Use Railway Web Interface (No CLI needed)

### Step 1: Deploy Backend on Railway

1. Go to [railway.app](https://railway.app) and sign in with GitHub
2. Click **"New Project"** → **"Deploy from GitHub repo"**
3. Select your `school-project` repository
4. Railway will detect the Dockerfile automatically
5. Click **"Deploy"**
6. Wait for build to complete (2-3 minutes)
7. Go to **Settings** → Copy your Railway URL (e.g., `https://school-backend-production.up.railway.app`)

### Step 2: Update Frontend API URL

Update the API URL in your frontend:

```bash
cd frontend/lib
```

Edit `api.js` and change line 3:
```javascript
const API_URL = 'https://YOUR-RAILWAY-URL.up.railway.app';
```

### Step 3: Deploy Frontend on Vercel

```bash
cd frontend
npx vercel
```

Follow the prompts:
- Set up and deploy? **Y**
- Which scope? (select your account)
- Link to existing project? **N**
- Project name? **school-frontend** (or any name)
- Directory? **./frontend** (press Enter)
- Override settings? **N**

Your app will be deployed! You'll get a URL like: `https://school-frontend.vercel.app`

---

## 🚀 Alternative: Use Render (All-in-One)

Even simpler - both services deploy together:

1. Go to [render.com](https://render.com) and sign in
2. Click **"New +"** → **"Blueprint"**
3. Connect your GitHub repository
4. Render will automatically use the `render.yaml` file
5. Click **"Apply"**
6. Wait 5-10 minutes for both services to deploy
7. Get your URLs from the Render dashboard

---

## 🏠 Quick Local Testing

To test locally before deploying:

```bash
# Start backend
cd backend
make clean
make
./school_server

# Start frontend (in new terminal)
cd frontend
npm run dev -- -p 3001
```

Visit: `http://localhost:3001`

---

## 🔧 Troubleshooting Railway Build

If Railway build fails with "Error 1":

**Option A: Use Railway Web Interface (Recommended)**
- Railway will automatically detect and fix issues
- Just push your code and let Railway handle it

**Option B: Fix Dockerfile locally**
```bash
cd backend
rm -f *.o school_server data.json
git add .dockerignore Dockerfile
git commit -m "Fix Docker build"
git push
```

Then redeploy on Railway.

---

## 📱 Share with Teachers

Once deployed, share:
- **Frontend URL**: `https://your-app.vercel.app`
- **Login Credentials**:
  - Teachers: `mrsmith` / `teacher123`
  - Students: `john` / `john123`

Teachers can access from any device with internet!

---

## 💡 Pro Tips

1. **Railway gives you $5 free credit** - enough for ~500 hours
2. **Vercel is 100% free** for hobby projects
3. **Push to GitHub** to trigger automatic redeployments
4. **Monitor usage** in Railway/Vercel dashboards

---

## Need Help?

If deployment fails:
1. Check build logs in Railway/Vercel dashboard
2. Ensure all files are committed to Git
3. Try the Render option (render.yaml already configured)
4. Use local deployment guide in DOCUMENTATION.md
