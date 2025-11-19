# School Management System - Frontend

Next.js frontend application with TypeScript and Tailwind CSS.

## Tech Stack

- **Framework**: Next.js 15 (App Router)
- **Language**: TypeScript
- **Styling**: Tailwind CSS
- **State Management**: React Hooks

## Getting Started

### Install Dependencies

```bash
npm install
```

### Run Development Server

```bash
npm run dev
```

Open [http://localhost:3000](http://localhost:3000) in your browser.

### Build for Production

```bash
npm run build
npm start
```

## Project Structure

```
frontend/
├── app/
│   ├── page.tsx          # Login page
│   ├── teacher/
│   │   └── page.tsx      # Teacher dashboard
│   ├── student/
│   │   └── page.tsx      # Student dashboard
│   ├── layout.tsx        # Root layout
│   └── globals.css       # Global styles
├── lib/
│   ├── api.ts            # API client functions
│   └── types.ts          # TypeScript type definitions
└── ...
```

## Environment Variables

Create a `.env.local` file (optional):

```env
NEXT_PUBLIC_API_URL=http://localhost:8080
```

Default value is `http://localhost:8080` if not specified.

## Features

### Login Page
- Clean authentication interface
- Role-based routing
- Error handling

### Teacher Dashboard
- View all students and grades
- Add/update/delete grades
- Form validation
- Real-time data refresh

### Student Dashboard
- View personal grades
- Performance statistics
- Average score calculation
- Color-coded grade indicators

## Code Quality

- ✅ TypeScript for type safety
- ✅ Well-commented sections
- ✅ Responsive design
- ✅ Clean component structure
- ✅ Error handling

## API Integration

All API calls are centralized in `lib/api.ts`:

- `login()` - User authentication
- `getAllStudents()` - Fetch all students
- `getAllGrades()` - Fetch all grades
- `getStudentGrades()` - Fetch grades for a student
- `addOrUpdateGrade()` - Create or update a grade
- `deleteGrade()` - Remove a grade

## Styling

Uses Tailwind CSS utility classes for:
- Responsive layouts
- Color schemes
- Hover effects
- Form styling
- Component design

## Notes

- Requires backend server running on port 8080
- Uses localStorage for session management
- Client-side routing with Next.js App Router
