import os
import sys

def format_inc_file(input_file):
    """Format a single .inc file and save the formatted content back to the same file."""
    print(f"Formatting file: {input_file}")
    
    # Read the input file
    with open(input_file, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Initialize variables
    formatted_content = []
    indent_level = 0
    in_string = False
    current_line = ""
    
    # Process each character
    for char in content:
        # Handle strings
        if char == '"' and (not current_line or current_line[-1] != '\\'):
            in_string = not in_string
            current_line += char
        
        # Handle opening braces
        elif char == '{' and not in_string:
            # Add the current line if it's not empty
            if current_line.strip():
                formatted_content.append('\t' * indent_level + current_line.strip())
            
            # Add the opening brace
            formatted_content.append('\t' * indent_level + '{')
            indent_level += 1
            current_line = ""
        
        # Handle closing braces
        elif char == '}' and not in_string:
            # Add the current line if it's not empty
            if current_line.strip():
                formatted_content.append('\t' * indent_level + current_line.strip())
            
            # Add the closing brace
            indent_level = max(0, indent_level - 1)
            formatted_content.append('\t' * indent_level + '}')
            current_line = ""
        
        # Handle newlines
        elif char == '\n' and not in_string:
            if current_line.strip():
                formatted_content.append('\t' * indent_level + current_line.strip())
            current_line = ""
        
        # Handle all other characters
        else:
            current_line += char
    
    # Add any remaining content
    if current_line.strip():
        formatted_content.append('\t' * indent_level + current_line.strip())
    
    # Write the formatted content back to the file
    with open(input_file, 'w', encoding='utf-8') as f:
        f.write('\n'.join(formatted_content))
    
    print(f"Successfully formatted: {input_file}")

def process_directory():
    """Find all .inc files in the current directory and format them."""
    current_dir = os.getcwd()
    print(f"Searching for .inc files in: {current_dir}")
    
    # Find all .inc files
    inc_files = [f for f in os.listdir(current_dir) if f.endswith('.inc')]
    
    if not inc_files:
        print("No .inc files found in the current directory.")
        return
    
    print(f"Found {len(inc_files)} .inc files: {', '.join(inc_files)}")
    
    # Format each file
    for file in inc_files:
        try:
            format_inc_file(file)
        except Exception as e:
            print(f"Error formatting {file}: {str(e)}")
    
    print("Formatting complete.")

if __name__ == "__main__":
    process_directory()
