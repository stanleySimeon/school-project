# Deployment Guide - School Management System

## Option 1: Quick Local Network Deployment (Recommended for Testing)

### Setup:
1. Build the backend:
   ```bash
   cd backend
   make
   ```

2. Start both servers:
   ```bash
   cd ..
   ./start-servers.sh
   ```

3. Share the Network URL with teachers (shown in terminal output)
   - Example: `http://192.168.1.100:3001`
   - Teachers must be on the same WiFi network

### To access from other devices:
- Make sure your firewall allows connections on ports 8080 and 3001
- On macOS: System Preferences → Security & Privacy → Firewall → Firewall Options

---

## Option 2: Cloud Deployment (Free Tier)

### A. Frontend on Vercel (Free)

1. Install Vercel CLI:
   ```bash
   npm i -g vercel
   ```

2. Deploy frontend:
   ```bash
   cd frontend
   vercel
   ```

3. Follow prompts and get your URL (e.g., `school-app.vercel.app`)

### B. Backend on Railway (Free)

1. Create account at [railway.app](https://railway.app)

2. Install Railway CLI:
   ```bash
   npm i -g @railway/cli
   railway login
   ```

3. Deploy backend:
   ```bash
   cd backend
   railway init
   railway up
   ```

4. Get your backend URL from Railway dashboard

5. Update frontend API URL:
   - Edit `frontend/lib/api.js`
   - Change `const API_URL = 'http://localhost:8080'` to your Railway URL

6. Redeploy frontend:
   ```bash
   cd frontend
   vercel --prod
   ```

---

## Option 3: Alternative - Render (All-in-One)

1. Create account at [render.com](https://render.com)

2. Push code to GitHub:
   ```bash
   git add .
   git commit -m "Ready for deployment"
   git push
   ```

3. On Render dashboard:
   - Click "New +" → "Blueprint"
   - Connect your GitHub repo
   - It will automatically detect `render.yaml` and deploy both services

4. Get your frontend URL from Render dashboard

---

## Option 4: Docker Compose (Local Production)

1. Install Docker Desktop

2. Create `docker-compose.yml` in project root (already created)

3. Start services:
   ```bash
   docker-compose up -d
   ```

4. Access at `http://localhost:3001`

5. To stop:
   ```bash
   docker-compose down
   ```

---

## For School Production Use

### Best Option: AWS/DigitalOcean (Paid but reliable)

**Cost:** ~$5-10/month for both services

**DigitalOcean App Platform:**
1. Create account at [digitalocean.com](https://digitalocean.com)
2. Create new app from GitHub repo
3. Configure:
   - Backend: Docker (using Dockerfile)
   - Frontend: Node.js
4. Deploy and get production URLs

**Benefits:**
- Always online
- Professional URLs
- Automatic SSL/HTTPS
- Better performance
- Automatic backups

---

## Access Information

### Default Credentials:

**Teachers:**
- Username: `mrsmith`, `msjones`, `mrwilson`, `msdavis`
- Password: `teacher123`

**Students:**
- Username: `john`, `jane`, `bob`
- Password: `john123`, `jane123`, `bob123`

---

## Troubleshooting

### Port already in use:
```bash
# Kill processes on port 8080 or 3001
lsof -ti:8080 | xargs kill -9
lsof -ti:3001 | xargs kill -9
```

### Backend not starting:
```bash
cd backend
make clean
make
./school_server
```

### Frontend not connecting to backend:
- Check `frontend/lib/api.js` has correct API_URL
- Verify backend is running on specified port
- Check CORS settings in `backend/http.cpp`

---

## Which Option to Choose?

- **Testing with 1-2 teachers:** Option 1 (Local Network)
- **School-wide deployment (free):** Option 2 (Vercel + Railway)
- **Professional deployment:** DigitalOcean or AWS
- **Local server (always on):** Docker Compose on dedicated machine
